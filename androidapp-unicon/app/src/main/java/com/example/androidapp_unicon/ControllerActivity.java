package com.example.androidapp_unicon;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class ControllerActivity extends AppCompatActivity {

    private Socket socket;

    private static final int SERVER_PORT = 8000;
    private static final String SERVER_IP = "10.0.0.34";
    private static final String default_op = "";
    private static final int REFRESH_RATE = 1;
    volatile boolean finished = false;

    private static volatile String output = default_op;
    private static byte[] bytes_op = null;

    private View.OnTouchListener handleTouch = new View.OnTouchListener() {

        @Override
        public boolean onTouch(View v, MotionEvent event) {

//            int x = (int) event.getX();
//            int y = (int) event.getY();

            char button;

            switch (v.getId()) {
                case (R.id.LEFT):
                    break;
                case (R.id.RIGHT):
                    break;
                case (R.id.A):
                    break;
                case (R.id.B):
                    break;
                case (R.id.X):
                    break;
                case (R.id.Y):
                    break;
                case (R.id.Z):
                    break;
            }

            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    Log.i("TAG", "touched down");
                    break;
                case MotionEvent.ACTION_MOVE:
//                    Log.i("TAG", "moving: (" + x + ", " + y + ")");
                    break;
                case MotionEvent.ACTION_UP:
                    Log.i("TAG", "touched up");
                    break;
            }

            return true;
        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);

        findViewById(R.id.LEFT).setOnTouchListener(handleTouch);
        findViewById(R.id.RIGHT).setOnTouchListener(handleTouch);
        findViewById(R.id.A).setOnTouchListener(handleTouch);
        findViewById(R.id.B).setOnTouchListener(handleTouch);
        findViewById(R.id.X).setOnTouchListener(handleTouch);
        findViewById(R.id.Y).setOnTouchListener(handleTouch);
        findViewById(R.id.Z).setOnTouchListener(handleTouch);

        new Thread(new ClientThread()).start();
    }

    public void onLeft(View view) { output += "L"; }

    public void onRight(View view) {
        output += "R";
    }

    public void onX(View view) { output += "X"; }

    public void onY(View view) {
        output += "Y";
    }

    public void onZ(View view) {
        output += "Z";
    }

    public void onB(View view) {
        output += "B";
    }

    public void onA(View view) {
        output += "A";
    }

    public void onStart(View view) {
        output += "S";
    }

    class ClientThread implements Runnable {

        @Override
        public void run() {

            PrintWriter out = null;
            DataOutputStream datastream = null;
            ByteArrayOutputStream bytestream = null;

            try {

                InetAddress serverAddr = InetAddress.getByName(SERVER_IP);
                socket = new Socket(serverAddr, SERVER_PORT);
                Log.i("connection", "the socket is initialized");


                //out = new PrintWriter(new BufferedWriter(
                //         OutputStreamWriter(socket.getOutputStream())), true);

                datastream = new DataOutputStream(socket.getOutputStream());

            } catch (UnknownHostException e1) {
                e1.printStackTrace();
                Log.i("error", "unknown");
            } catch (IOException e1) {
                e1.printStackTrace();
                Log.i("error", "io");
            } catch (Exception e) {
                e.printStackTrace();
                Log.i("error", "e");
            }

            while(!Thread.currentThread().isInterrupted()) {
                talkToServer(datastream);
            }

        }

        public void stopMe() {
            finished = true;
        }

        public void talkToServer(DataOutputStream stream) {
            try {
                Thread.sleep(REFRESH_RATE); }
            catch (Exception e) {
                e.printStackTrace(); }

            try{
                stream.write(bytes_op);
                stream.flush(); }

                catch (IOException e){
                e.printStackTrace();
                Log.i("error", "talk to server io exception");
            }
            output = default_op;

        }


    }

}
