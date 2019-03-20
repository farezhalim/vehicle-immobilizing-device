package com.example.immobilizer;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.TextView;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;

public class WriteSDCard extends Activity {

    private static final String TAG = "MEDIA";
    private TextView tv;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {

        Log.d(TAG, "onCreate: WriteSDCard class created");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        tv = (TextView) findViewById(R.id.textView_key);
        checkExternalMedia();
        //writeToSDFile();
        //readRaw();
    }

    /** Method to check whether external media available and writable. This is adapted from
     http://developer.android.com/guide/topics/data/data-storage.html#filesExternal */

    private void checkExternalMedia(){
        boolean mExternalStorageAvailable = false;
        boolean mExternalStorageWriteable = false;
        String state = Environment.getExternalStorageState();

        if (Environment.MEDIA_MOUNTED.equals(state)) {
            // Can read and write the media
            mExternalStorageAvailable = mExternalStorageWriteable = true;
        } else if (Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) {
            // Can only read the media
            mExternalStorageAvailable = true;
            mExternalStorageWriteable = false;
        } else {
            // Can't read or write
            mExternalStorageAvailable = mExternalStorageWriteable = false;
        }

    }

    /** Method to write ascii text characters to file on SD card. Note that you must add a
     WRITE_EXTERNAL_STORAGE permission to the manifest file or this method will throw
     a FileNotFound Exception because you won't have write permission. */

    public void writeToSDFile(){

        // Find the root of the external storage.
        // See http://developer.android.com/guide/topics/data/data-  storage.html#filesExternal

        File root = android.os.Environment.getExternalStorageDirectory();

        // See http://stackoverflow.com/questions/3551821/android-write-to-sd-card-folder

        File dir = new File (root.getAbsolutePath() + "/Documents");
        dir.mkdirs();
        File file = new File(dir, "key.txt");

        try {
            FileOutputStream f = new FileOutputStream(file);
            PrintWriter pw = new PrintWriter(f);
            pw.println(tv.getText().toString());
            pw.flush();
            pw.close();
            f.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            Log.i(TAG, "******* File not found. Did you" +
                    " add a WRITE_EXTERNAL_STORAGE permission to the   manifest?");
        } catch (IOException e) {
            e.printStackTrace();
        }

        Log.d(TAG, "writeToSDFile: File written to "+ file);
    }

    /** Method to read in a text file placed in the res/raw directory of the application. The
     method reads in all lines of the file sequentially.

    private void readRaw(){
        tv.append("\nData read from res/raw/key.txt:");
        InputStream is = this.getResources().openRawResource(R.raw.textfile);
        InputStreamReader isr = new InputStreamReader(is);
        BufferedReader br = new BufferedReader(isr, 8192);    // 2nd arg is buffer size

        // More efficient (less readable) implementation of above is the composite expression
    // BufferedReader br = new BufferedReader(new InputStreamReader(this.getResources().openRawResource(R.raw.textfile)), 8192);

        try {
            String test;
            while (true){
                test = br.readLine();
                // readLine() returns null if no more lines in the file
                if(test == null) break;
                tv.append("\n"+"    "+test);
            }
            isr.close();
            is.close();
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        tv.append("\n\nThat is all");
    }

    */
}

