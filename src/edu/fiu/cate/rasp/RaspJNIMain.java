package edu.fiu.cate.rasp;

public class RaspJNIMain {

	public static void main(String[] args) {
		I2C i2c = I2C.getI2C(1, 8);
		
		int pwm = 0;
		while(true){
			i2c.writeRead(new byte[]{0x10, (byte)(pwm++), (byte)(pwm++), (byte)(pwm++)}, 1);
			i2c.writeByte((byte)1);
			System.out.println("Writing: "+pwm);
			
			if(pwm>100)
				pwm = 0;
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

	}

}
