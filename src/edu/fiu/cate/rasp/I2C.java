package edu.fiu.cate.rasp;

public class I2C {
	
	private int handler = -1;
	private int bus		= -1;
	private int address = -1;
	
	static{
		try{
			System.loadLibrary("RaspberryPiJNI");
		}catch(UnsatisfiedLinkError e){
			System.err.println("Library libRaspberryPiJNI.so does not exist in library path:");
			System.err.println(System.getProperty("java.library.path"));
		}catch(SecurityException e){
			e.printStackTrace();
		}
	}

//Native Methods
	
	private native int open(char bus);
	private native int setSlaveAddress(int bus, long addr);
	
//	private native int open(char bus, char addr);

	// These functions return -1 on error, otherwise return the number of bytes read/written.
	// To perform a 'repeated start' use the i2c_write_read function which can write some
	// data and then immediately read data without a stop bit in between.
	private native int write(int handle, byte[] buf);

	private native byte[] read(int handle, int lenght);

	private native byte[] writeRead(int handle, byte addr, byte[] buf_w, int len_r);

	private native int writeIgnoreNack(int handle, byte addr, byte[] buf);

	private native byte[] readNoAck(int handle, int addr, int lenght);

	private native int writeByte(int handle, byte val);

	public native int readByte(int handle);

	// These functions return -1 on error, otherwise return 0 on success
	public native int close(int handle);
	
//End Native Methods
	
	private I2C(){};
	
 	public static I2C getI2C(int bus){
		if(bus<0)return null;
		I2C i2c = new I2C();
		i2c.handler = i2c.open((char)bus);
		if( i2c.handler < 0) return null;
		i2c.bus = bus;
		return i2c;
	}
	
	public static I2C getI2C(int bus, int slaveAddress){
		I2C i2c = getI2C(bus);
		if(i2c == null)return null;
		if(!i2c.setSlaveAddress(slaveAddress))return null;
		return i2c;
	}

	public synchronized boolean setSlaveAddress(int address){
		if(address < 0 || address > 255) return false;
		if(this.address == address) return true;
		int reply = setSlaveAddress(this.handler, address);
		if(reply < 0) return false;
		this.address = address;
		return true;
	}
	public int getSlaveAddress(){
		return this.address;
	}

	public synchronized int write(byte[] buf){
		return write(this.handler, buf);
	}
	
	public synchronized byte[] read(int lenght){
		return read(this.handler, lenght);
	}

	public synchronized byte[] writeRead(byte[] buf_w, int len_r){
		return writeRead(this.handler, (byte)this.address, buf_w, len_r);
	}
	
	public synchronized int writeIgnoreNack(byte[] buf){
		return writeIgnoreNack(this.handler, (byte)this.address, buf);
	}
	
	public synchronized byte[] readNoAck(int lenght){
		return readNoAck(this.handler, (byte)this.address, lenght);
	}
	
	public synchronized int writeByte(byte val){
		return writeByte(this.handler, val);
	}

	public synchronized byte[] readRegister(byte reg, int len){
		return writeRead(new byte[]{reg}, len);
	}
	
	public synchronized boolean writeRegister(byte reg, byte[] data){
		byte[] buf = new byte[data.length + 1];
		buf[0] = reg;
		for(int i = 0; i < data.length; i++)
			buf[i+1] = data[i];
		return !(write(buf)<0);
	}
}