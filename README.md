
# es-sensor 2.0


## Requirements


avro-c-1.7.7 


```
$  sudo apt install git-core cmake  librtlsdr-dev librtlsdr0 libliquid1d libliquid-dev liblzma-dev liblzma5 libssl1.0-dev
```

## Compile

```
$ git clone $REPO
$ cmake .
$ make 
```

## Run

* Storage the measurements to a file

```
./es_sensor 24000000 1600000000 -u /tmp/measurements.csv
```

* Send the spectrum measurements to the backend 

```
./es_sensor 24000000 1600000000 -n collector.electrosense.org:5001#certs/CA-Cert.pem#certs/Sensor-SSL-Cert.pem#certs/Sensor-SSL-SK.pem
```