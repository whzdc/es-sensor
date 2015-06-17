/**
 * Autogenerated by Avro
 * 
 * DO NOT EDIT DIRECTLY
 */
package ch.electrosense.avro.v1;  
@SuppressWarnings("all")
@org.apache.avro.specific.AvroGenerated
public class SenPosRec extends org.apache.avro.specific.SpecificRecordBase implements org.apache.avro.specific.SpecificRecord {
  public static final org.apache.avro.Schema SCHEMA$ = new org.apache.avro.Schema.Parser().parse("{\"type\":\"record\",\"name\":\"SenPosRec\",\"namespace\":\"ch.electrosense.avro.v1\",\"fields\":[{\"name\":\"PosSys\",\"type\":\"string\",\"doc\":\"Description/identification of the used positioning system.\"},{\"name\":\"PosVal\",\"type\":{\"type\":\"array\",\"items\":\"float\"},\"doc\":\"Position values in the corresponding positioning system.\"}]}");
  public static org.apache.avro.Schema getClassSchema() { return SCHEMA$; }
  /** Description/identification of the used positioning system. */
  @Deprecated public java.lang.CharSequence PosSys;
  /** Position values in the corresponding positioning system. */
  @Deprecated public java.util.List<java.lang.Float> PosVal;

  /**
   * Default constructor.  Note that this does not initialize fields
   * to their default values from the schema.  If that is desired then
   * one should use <code>newBuilder()</code>. 
   */
  public SenPosRec() {}

  /**
   * All-args constructor.
   */
  public SenPosRec(java.lang.CharSequence PosSys, java.util.List<java.lang.Float> PosVal) {
    this.PosSys = PosSys;
    this.PosVal = PosVal;
  }

  public org.apache.avro.Schema getSchema() { return SCHEMA$; }
  // Used by DatumWriter.  Applications should not call. 
  public java.lang.Object get(int field$) {
    switch (field$) {
    case 0: return PosSys;
    case 1: return PosVal;
    default: throw new org.apache.avro.AvroRuntimeException("Bad index");
    }
  }
  // Used by DatumReader.  Applications should not call. 
  @SuppressWarnings(value="unchecked")
  public void put(int field$, java.lang.Object value$) {
    switch (field$) {
    case 0: PosSys = (java.lang.CharSequence)value$; break;
    case 1: PosVal = (java.util.List<java.lang.Float>)value$; break;
    default: throw new org.apache.avro.AvroRuntimeException("Bad index");
    }
  }

  /**
   * Gets the value of the 'PosSys' field.
   * Description/identification of the used positioning system.   */
  public java.lang.CharSequence getPosSys() {
    return PosSys;
  }

  /**
   * Sets the value of the 'PosSys' field.
   * Description/identification of the used positioning system.   * @param value the value to set.
   */
  public void setPosSys(java.lang.CharSequence value) {
    this.PosSys = value;
  }

  /**
   * Gets the value of the 'PosVal' field.
   * Position values in the corresponding positioning system.   */
  public java.util.List<java.lang.Float> getPosVal() {
    return PosVal;
  }

  /**
   * Sets the value of the 'PosVal' field.
   * Position values in the corresponding positioning system.   * @param value the value to set.
   */
  public void setPosVal(java.util.List<java.lang.Float> value) {
    this.PosVal = value;
  }

  /** Creates a new SenPosRec RecordBuilder */
  public static ch.electrosense.avro.v1.SenPosRec.Builder newBuilder() {
    return new ch.electrosense.avro.v1.SenPosRec.Builder();
  }
  
  /** Creates a new SenPosRec RecordBuilder by copying an existing Builder */
  public static ch.electrosense.avro.v1.SenPosRec.Builder newBuilder(ch.electrosense.avro.v1.SenPosRec.Builder other) {
    return new ch.electrosense.avro.v1.SenPosRec.Builder(other);
  }
  
  /** Creates a new SenPosRec RecordBuilder by copying an existing SenPosRec instance */
  public static ch.electrosense.avro.v1.SenPosRec.Builder newBuilder(ch.electrosense.avro.v1.SenPosRec other) {
    return new ch.electrosense.avro.v1.SenPosRec.Builder(other);
  }
  
  /**
   * RecordBuilder for SenPosRec instances.
   */
  public static class Builder extends org.apache.avro.specific.SpecificRecordBuilderBase<SenPosRec>
    implements org.apache.avro.data.RecordBuilder<SenPosRec> {

    private java.lang.CharSequence PosSys;
    private java.util.List<java.lang.Float> PosVal;

    /** Creates a new Builder */
    private Builder() {
      super(ch.electrosense.avro.v1.SenPosRec.SCHEMA$);
    }
    
    /** Creates a Builder by copying an existing Builder */
    private Builder(ch.electrosense.avro.v1.SenPosRec.Builder other) {
      super(other);
      if (isValidValue(fields()[0], other.PosSys)) {
        this.PosSys = data().deepCopy(fields()[0].schema(), other.PosSys);
        fieldSetFlags()[0] = true;
      }
      if (isValidValue(fields()[1], other.PosVal)) {
        this.PosVal = data().deepCopy(fields()[1].schema(), other.PosVal);
        fieldSetFlags()[1] = true;
      }
    }
    
    /** Creates a Builder by copying an existing SenPosRec instance */
    private Builder(ch.electrosense.avro.v1.SenPosRec other) {
            super(ch.electrosense.avro.v1.SenPosRec.SCHEMA$);
      if (isValidValue(fields()[0], other.PosSys)) {
        this.PosSys = data().deepCopy(fields()[0].schema(), other.PosSys);
        fieldSetFlags()[0] = true;
      }
      if (isValidValue(fields()[1], other.PosVal)) {
        this.PosVal = data().deepCopy(fields()[1].schema(), other.PosVal);
        fieldSetFlags()[1] = true;
      }
    }

    /** Gets the value of the 'PosSys' field */
    public java.lang.CharSequence getPosSys() {
      return PosSys;
    }
    
    /** Sets the value of the 'PosSys' field */
    public ch.electrosense.avro.v1.SenPosRec.Builder setPosSys(java.lang.CharSequence value) {
      validate(fields()[0], value);
      this.PosSys = value;
      fieldSetFlags()[0] = true;
      return this; 
    }
    
    /** Checks whether the 'PosSys' field has been set */
    public boolean hasPosSys() {
      return fieldSetFlags()[0];
    }
    
    /** Clears the value of the 'PosSys' field */
    public ch.electrosense.avro.v1.SenPosRec.Builder clearPosSys() {
      PosSys = null;
      fieldSetFlags()[0] = false;
      return this;
    }

    /** Gets the value of the 'PosVal' field */
    public java.util.List<java.lang.Float> getPosVal() {
      return PosVal;
    }
    
    /** Sets the value of the 'PosVal' field */
    public ch.electrosense.avro.v1.SenPosRec.Builder setPosVal(java.util.List<java.lang.Float> value) {
      validate(fields()[1], value);
      this.PosVal = value;
      fieldSetFlags()[1] = true;
      return this; 
    }
    
    /** Checks whether the 'PosVal' field has been set */
    public boolean hasPosVal() {
      return fieldSetFlags()[1];
    }
    
    /** Clears the value of the 'PosVal' field */
    public ch.electrosense.avro.v1.SenPosRec.Builder clearPosVal() {
      PosVal = null;
      fieldSetFlags()[1] = false;
      return this;
    }

    @Override
    public SenPosRec build() {
      try {
        SenPosRec record = new SenPosRec();
        record.PosSys = fieldSetFlags()[0] ? this.PosSys : (java.lang.CharSequence) defaultValue(fields()[0]);
        record.PosVal = fieldSetFlags()[1] ? this.PosVal : (java.util.List<java.lang.Float>) defaultValue(fields()[1]);
        return record;
      } catch (Exception e) {
        throw new org.apache.avro.AvroRuntimeException(e);
      }
    }
  }
}
