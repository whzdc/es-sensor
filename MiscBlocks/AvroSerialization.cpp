//
// Created by rocapal on 26/03/18.
//

#include "AvroSerialization.h"



namespace electrosense {


    AvroSerialization::AvroSerialization() {
        mQueueOut = new ReaderWriterQueue<SpectrumSegment *>(100);
    }

    void AvroSerialization::run() {

        std::cout << "[*] AvroSerialization block running .... " << std::endl;

        char                 *json_schema;
        const char           *json_schema_file = "schema/rtl-spec.avsc";
        avro_schema_t        avro_schema = NULL;

        mRunning = true;
        SpectrumSegment *segment;

        if (mQueueIn == NULL || mQueueOut == NULL) {
            throw std::logic_error("Queue[IN|OUT] are NULL!");
        }

        unsigned int fft_size = 1<<ElectrosenseContext::getInstance()->getLog2FftSize();
        unsigned int reduced_fft_size = (1 - ElectrosenseContext::getInstance()->getFreqOverlap())*(fft_size + 1);
        float freq_res = ((float) ElectrosenseContext::getInstance()->getSamplingRate()) / fft_size;

        // Read JSON schema from file
        FILE *file = fopen(json_schema_file, "r");
        if(file == NULL) {
            fprintf(stderr, "[AvroSerialization] Failed to open file %s.\n", json_schema_file);
            exit(1);
        }
        fseek(file, 0, SEEK_END);
        int file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        json_schema = (char *) malloc(file_size+1);
        size_t read = fread(json_schema, 1, file_size, file);
        if(read != file_size) {
            fprintf(stderr, "[AvroSerialization] File %s incompletely read.\n", json_schema_file);
            exit(1);
        }
        json_schema[file_size] = '\0';
        fclose(file);

        // Parse JSON schema into C API's internal schema representation
        avro_schema_from_json(json_schema, 0, &avro_schema, NULL);
        if(avro_schema == NULL) {
            fprintf(stderr, "[AvroSerialization] Failed to parse AVRO schema.\n");
            exit(1);
        }
        // Release JSON schema
        free(json_schema);

        avro_value_iface_t *avro_iface = avro_generic_class_from_schema(avro_schema);

        long long mac_eth0_dec;
        get_mac_address_eth0(&mac_eth0_dec);

        while (mRunning) {

            if (mQueueIn && mQueueIn->try_dequeue(segment)) {


                unsigned int buf_size = ((5*4+fft_size*4) + 3) & ~0x03;
                char* buf = (char *) malloc(buf_size);

                // Create Avro memory writer
                avro_writer_t avro_writer = avro_writer_memory(buf, buf_size);

                // Create a value that is an instance of that schema
                avro_value_t avro_value_sample;

                avro_generic_value_new(avro_iface, &avro_value_sample);

                // Unique sensor identifier (required)
                avro_value_t avro_value_sen_id;
                avro_value_get_by_name(&avro_value_sample, "SenId", &avro_value_sen_id, NULL);


                avro_value_set_long(&avro_value_sen_id, mac_eth0_dec);

                // Sensor configuration (required)
                avro_value_t avro_value_sen_conf, avro_value_hopping_strategy, avro_value_windowing_function,
                        avro_value_fft_size, avro_value_averaging_factor, avro_value_frequency_overlap,
                        avro_value_freq_res, avro_value_gain;

                avro_value_get_by_name(&avro_value_sample, "SenConf", &avro_value_sen_conf, NULL);
                avro_value_get_by_name(&avro_value_sen_conf, "HoppingStrategy", &avro_value_hopping_strategy, NULL);
                avro_value_set_int(&avro_value_hopping_strategy, 0); // Sequential
                avro_value_get_by_name(&avro_value_sen_conf, "WindowingFunction", &avro_value_windowing_function, NULL);
                avro_value_set_int(&avro_value_windowing_function, 1); // Hamming
                avro_value_get_by_name(&avro_value_sen_conf, "FFTSize", &avro_value_fft_size, NULL);
                avro_value_set_int(&avro_value_fft_size, fft_size);
                avro_value_get_by_name(&avro_value_sen_conf, "AveragingFactor", &avro_value_averaging_factor, NULL);
                avro_value_set_int(&avro_value_averaging_factor, ElectrosenseContext::getInstance()->getAvgFactor());
                avro_value_get_by_name(&avro_value_sen_conf, "FrequencyOverlap", &avro_value_frequency_overlap, NULL);
                avro_value_set_float(&avro_value_frequency_overlap, ElectrosenseContext::getInstance()->getFreqOverlap());
                avro_value_get_by_name(&avro_value_sen_conf, "FrequencyResolution", &avro_value_freq_res, NULL);
                avro_value_set_float(&avro_value_freq_res, freq_res);
                avro_value_get_by_name(&avro_value_sen_conf, "Gain", &avro_value_gain, NULL);
                avro_value_set_float(&avro_value_gain, ElectrosenseContext::getInstance()->getGain());

                int set_sen_pos = 0;
                avro_value_t avro_value_sen_pos, avro_value_sen_pos_rec;
                avro_value_get_by_name(&avro_value_sample, "SenPos", &avro_value_sen_pos, NULL);
                //TODO: Sensor position (optional)
                avro_value_set_branch(&avro_value_sen_pos, 0, &avro_value_sen_pos_rec);
                avro_value_set_null(&avro_value_sen_pos_rec);

                // Sensor temperature (optional)
                int set_sen_temp = 0;
                avro_value_t avro_value_sen_temp, avro_value_branch;
                avro_value_get_by_name(&avro_value_sample, "SenTemp", &avro_value_sen_temp, NULL);
                if(set_sen_temp) {
                    avro_value_set_branch(&avro_value_sen_temp, 1, &avro_value_branch);
                    avro_value_set_float(&avro_value_branch, 0.f);
                } else {
                    avro_value_set_branch(&avro_value_sen_temp, 0, &avro_value_branch);
                    avro_value_set_null(&avro_value_branch);
                }

                // Sensor time (required)
                avro_value_t avro_value_sen_time, avro_value_time_secs, avro_value_time_microsecs;
                avro_value_get_by_name(&avro_value_sample, "SenTime", &avro_value_sen_time, NULL);
                avro_value_get_by_name(&avro_value_sen_time, "TimeSecs", &avro_value_time_secs, NULL);
                avro_value_set_long(&avro_value_time_secs, segment->getTimeStamp().tv_sec);
                avro_value_get_by_name(&avro_value_sen_time, "TimeMicrosecs", &avro_value_time_microsecs, NULL);
                avro_value_set_int(&avro_value_time_microsecs, segment->getTimeStamp().tv_nsec);

                // Sensor data (required)
                avro_value_t avro_value_sen_data, avro_value_center_freq, avro_value_squared_mag;
                avro_value_get_by_name(&avro_value_sample, "SenData", &avro_value_sen_data, NULL);
                avro_value_get_by_name(&avro_value_sen_data, "CenterFreq", &avro_value_center_freq, NULL);
                avro_value_set_long(&avro_value_center_freq,  (uint64_t) segment->getCenterFrequency());
                avro_value_get_by_name(&avro_value_sen_data, "SquaredMag", &avro_value_squared_mag, NULL);

                // We need an odd number of bins
                if (reduced_fft_size % 2 == 0)
                    reduced_fft_size++;

                avro_value_t avro_value_element;
                unsigned int l = round((fft_size - reduced_fft_size) / 2);

                for(unsigned int i=0; i<reduced_fft_size; ++i) {
                    size_t new_index;
                    float s = (segment->getPSDValues()[l+i]);

                    avro_value_append(&avro_value_squared_mag, &avro_value_element, &new_index);
                    if(new_index != i) {
                        fprintf(stderr, "[AvroSerialization] ERROR: Unexpected index.\n");
                        exit(1);
                    }
                    avro_value_set_float(&avro_value_element, s);
                }

                avro_value_decref(&avro_value_element);
                avro_value_write(avro_writer, &avro_value_sample);

                segment->setAvroBuffer(buf, buf_size);

                mQueueOut->enqueue(segment);



            } else
                usleep(1);
        }

        avro_value_iface_decref(avro_iface);
        avro_schema_decref(avro_schema);

    }

    int AvroSerialization::get_mac_address_eth0(long long *mac_dec) {
        int sock;
        const char *ifname = "eth0";
        char mac_hex[19];
        struct ifreq ifr;

        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(sock < 0) return -1;
        strcpy(ifr.ifr_name, ifname);
        ifr.ifr_addr.sa_family = AF_INET;
        if(ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) return -2;

        // MAC address hexadecimal
        sprintf(mac_hex, "%02x%02x%02x%02x%02x%02x",
                (unsigned char) ifr.ifr_hwaddr.sa_data[0],
                (unsigned char) ifr.ifr_hwaddr.sa_data[1],
                (unsigned char) ifr.ifr_hwaddr.sa_data[2],
                (unsigned char) ifr.ifr_hwaddr.sa_data[3],
                (unsigned char) ifr.ifr_hwaddr.sa_data[4],
                (unsigned char) ifr.ifr_hwaddr.sa_data[5]
        );

        // MAC address decimal
        *mac_dec = strtoll(mac_hex, NULL, 16);

        return 0;
    }


    int AvroSerialization::stop() {

        mRunning = false;
        waitForThread();

        return 1;

    }
}