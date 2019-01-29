package com.example.androidapp_unicon;

import android.content.Intent;
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
import java.util.Timer;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


public class MainActivity extends AppCompatActivity {

    private static final String default_op = "";
    private static volatile String output = default_op;

    public static final String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //new Thread(new ClientThread()).start();

    }

    /** Called when the user taps the Send button */
    public void sendMessage(View view) {
        Intent intent = new Intent(this, ControllerActivity.class);
        EditText et = (EditText) findViewById(R.id.EditText01);
        output = et.getText().toString();
        intent.putExtra(EXTRA_MESSAGE, output);
        startActivity(intent);
    }



    public void onClick(View view) {
        Log.i("onclick", "click method calling");

        EditText et = (EditText) findViewById(R.id.EditText01);
        output = et.getText().toString();
        Log.i("onclick", "Sent: " + output);

    }


//    public void onLeft(View view, MotionEvent event) {
//        switch(event.getAction()) {
//            case MotionEvent.ACTION_DOWN:
//                output += "left down";
//                break;
//
//            case MotionEvent.ACTION_UP:
//            case MotionEvent.ACTION_CANCEL:
//                output += "left released";
//        }
//
//    }


}

