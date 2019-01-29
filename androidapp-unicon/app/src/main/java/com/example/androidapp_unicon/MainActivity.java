package com.example.androidapp_unicon;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Logger;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.view.View.OnClickListener;

public class MainActivity extends AppCompatActivity {

    private Socket socket;

    private static final int SERVERPORT = 8000;
    private static final String SERVER_IP = "10.0.0.34";
    private static volatile String output = "";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        new Thread(new ClientThread()).start();

    }


    public void onClick(View view) {
        Log.i("onclick", "click method calling");

        EditText et = (EditText) findViewById(R.id.EditText01);
        output = et.getText().toString();
        Log.i("onclick", "Sent: " + output);
//        try {
//            //EditText et = (EditText) findViewById(R.id.EditText01);
//            //String str = et.getText().toString();
//            PrintWriter out = new PrintWriter(new BufferedWriter(
//                    new OutputStreamWriter(socket.getOutputStream())),
//                    true);
//            out.println("pt.2 where space tho");
//            Log.i("onclick", "ENTERING TRY STATEMENT YEAHHH");
//        } catch (UnknownHostException e) {
//            e.printStackTrace();
//        } catch (IOException e) {
//            e.printStackTrace();
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
    }



    class ClientThread implements Runnable {

        @Override
        public void run() {


            PrintWriter out = null;

            try {
                InetAddress serverAddr = InetAddress.getByName(SERVER_IP);

                socket = new Socket(serverAddr, SERVERPORT);
                Log.i("s", "the socket is initializing");
                out = new PrintWriter(new BufferedWriter(
                        new OutputStreamWriter(socket.getOutputStream())),
                        true);
            } catch (UnknownHostException e1) {
                e1.printStackTrace();
                Log.i("e1error", "unknown");
            } catch (IOException e1) {
                e1.printStackTrace();
                Log.i("e1error", "io");
            }

            while(true) {
                try{ Thread.sleep(1000); }catch(Exception e){ e.printStackTrace(); }
                out.println(output);
                output = "Empty";
            }
//            OutputStream stream = socket.getOutputStream();
//            stream.write(70);

        }

    }

}

