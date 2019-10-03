int echoPin = 8;
int trigPin = 9;
 
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  int duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(200);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(200);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration / 58;
  Serial.print(cm);
  Serial.println("");
  delay(2000);
}
 

Додаток В
Код класу з’єднання застосування з Bluetooth-модулем
package com.example.distansespeaker;
import java.io.IOException;
import java.lang.reflect.Method;
import java.util.Set;
import java.util.UUID;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Build;
import android.util.Log;
import android.widget.Toast;

public class DeviceConnect extends Activity {
	private static final String address = "98:D3:31:B4:25:58"; //MAC address of bluetooth
	private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); //unique identifier
	final int RECIEVE_MESSAGE = 1;        // Status of Handler
	private BluetoothAdapter btAdapter = null; //bluetooth adapter of android device
	private BluetoothSocket btSocket = null; //bluetooth socket for creating connection between devices
	private static final String TAG = "bluetooth2"; //tag for bluetooth logging
	private ErrorShow error = new ErrorShow();
	BluetoothDevice device;
	
	public DeviceConnect() {
		btAdapter = BluetoothAdapter.getDefaultAdapter();
	}
	
	
public Intent checkBTState() {
	    // Check for Bluetooth support and then check to make sure it is turned on
	    // Emulator doesn't support Bluetooth and will return null
	    if(btAdapter==null) {
	      error.errorExit("Fatal Error", "Bluetooth not supported.");
	    } else {
	      if (btAdapter.isEnabled()) { //check if bluetooth is enabled
	        Log.d(TAG, "...Bluetooth is turned on...");
	        return null;
	      } else {
	        //Prompt user to turn on Bluetooth
	    	  Intent enableBtIntent = new Intent(btAdapter.ACTION_REQUEST_ENABLE);
	    	  return enableBtIntent;
	      }
	    }
	    return null;
	}
	
	public void closeSocket() {
		try {
			btSocket.close();
		}
		catch (Exception e) {
			error.errorExit("Error", "Unable to close bleutooth socket.");
		}
	}	
	public void errorExit(String title, String message){
	    Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
	    finish();
	}
	
	public BluetoothDevice getDevice() {
		return btAdapter.getRemoteDevice(address);
	}
	
	public boolean checkPaired() {
		Set<BluetoothDevice> pairedDevices 
		   = btAdapter.getBondedDevices();
		boolean found = false;
		for(BluetoothDevice bt : pairedDevices) {
			if (bt.getAddress().equals(address)) {
					found = true;
			}
		}
		return found;
	}
	
	public BluetoothSocket connect() {
		device = btAdapter.getRemoteDevice(address);
		
		try {	    	
	         btSocket = createBluetoothSocket(device);
	         //
	    } catch (Exception e) {	    	
	      errorExit("Fatal Error", "In onResume() and socket create failed: " + e.getMessage() + ".");
	    }
		
	    // Discovery is resource intensive.  Make sure it isn't going on
	    // when you attempt to connect and pass your message.
	    btAdapter.cancelDiscovery();
	    
	    try {
	      btSocket.connect();
	      return btSocket;
	    } catch (Exception e) {
	      try {
	    	btSocket.close();
	    	
	      } catch (Exception e2) {
	        errorExit("Fatal Error", "In onResume() and unable to close socket during connection failure" + e2.getMessage() + ".");
	      }
	    }
	    return null;
	}
	
	private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        if(Build.VERSION.SDK_INT >= 10){
            try {
                final Method  m = device.getClass().getMethod("createInsecureRfcommSocketToServiceRecord", new Class[] { UUID.class });
                return (BluetoothSocket) m.invoke(device, MY_UUID);
            } catch (Exception e) {
                Log.e("No Connection Created", "Could not create Insecure RFComm Connection",e);
            }
        }
        return  device.createRfcommSocketToServiceRecord(MY_UUID);
    }
}
 
