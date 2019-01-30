package com.example.androidapp_unicon;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Timer;

public class ControllerActivity extends AppCompatActivity {

    private Socket socket;

    private static final int SERVER_PORT = 8000;
    private static final String SERVER_IP = "10.0.0.34";
    private static final String default_op = "";
    private static final int REFRESH_RATE = 1;
    volatile boolean finished = false;

    private static volatile String output = default_op;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);

        new Thread(new ClientThread()).start();
    }

    public void onLeft(View view) {
        output += "L";
    }

    public void onRight(View view) {
        output += "R";
    }

    public void onX(View view) {
        output += "X";
    }

    public void onY(View view) {
        output += "Y";
    }

    public void onZ(View view) {
        output += "Z";
    }

    class ClientThread implements Runnable {

        @Override
        public void run() {

            PrintWriter out = null;

            try {

                InetAddress serverAddr = InetAddress.getByName(SERVER_IP);
                socket = new Socket(serverAddr, SERVER_PORT);


                Log.i("connection", "the socket is initialized");
                out = new PrintWriter(new BufferedWriter(
                        new OutputStreamWriter(socket.getOutputStream())),
                        true);

            } catch (UnknownHostException e1) {
                e1.printStackTrace();
                Log.i("e1error", "unknown");
            } catch (IOException e1) {
                e1.printStackTrace();
                Log.i("e1error", "io");
            } catch (Exception e) {
                e.printStackTrace();
                Log.i("error", "e");
            }

            while(!Thread.currentThread().isInterrupted()) {
                talkToServer(out);
            }

        }

        public void stopMe() {
            finished = true;
        }

        public void talkToServer(PrintWriter out) {
            try {
                Thread.sleep(REFRESH_RATE); }
            catch (Exception e) {
                e.printStackTrace(); }

            if (output != "") {
                out.print(output);
            }
            output = default_op;

        }

    }

}
