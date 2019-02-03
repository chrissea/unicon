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

import com.jmedeisis.bugstick.Joystick;
import com.jmedeisis.bugstick.JoystickListener;

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

import static java.lang.Math.*;


public class ControllerActivity extends AppCompatActivity {

    private Socket socket;

    private static final int SERVER_PORT = 8000;
    private static final String SERVER_IP = "10.0.0.108";
    private static final String default_op = "";
    private static final int REFRESH_RATE = 100;
    //volatile boolean finished = false;

    private static volatile String output = default_op;
    private static byte[] bytes_op = {0x8, 0x8, 0x8, 0x8};
    // b0: A B Z S  -  -  -  -
    // b1: 0 0 L R CU CD CL CR
    // b2: Joystick X
    // b3: Joystick Y

    private static boolean connected = false;
    private static boolean LEFTheld = false;
    private static boolean RIGHTheld = false;
    private static boolean Aheld = false;
    private static boolean Bheld = false;
    private static boolean Xheld = false;
    private static boolean Yheld = false;
    private static boolean Zheld = false;
    private static boolean CUheld = false;
    private static boolean CDheld = false;
    private static boolean CLheld = false;
    private static boolean CRheld = false;
    private static boolean[] sad = {LEFTheld, RIGHTheld, Aheld, Bheld, Zheld, CUheld, CDheld, CLheld, CRheld};
    private static double x = 0;
    private static double y = 0;

    private View.OnTouchListener handleTouch = new View.OnTouchListener() {
        @Override
        public boolean onTouch(View v, MotionEvent event) {

            char button;

            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    switch (v.getId()) {
                        case (R.id.LEFT):
                            LEFTheld = !LEFTheld;
                            break;
                        case (R.id.RIGHT):
                            RIGHTheld = !RIGHTheld;
                            break;
                        case (R.id.A):
                            Aheld = !Aheld;
                            break;
                        case (R.id.B):
                            Bheld = !Bheld;
                            break;
                        case (R.id.Z):
                            Zheld = !Zheld;
                            break;
                        case (R.id.CU):
                            CUheld = !CUheld;
                        case (R.id.CD):
                            CDheld = !CDheld;
                        case (R.id.CL):
                            CLheld = !CLheld;
                        case (R.id.CR):
                            CRheld = !CRheld;

                    }
                    break;
                case MotionEvent.ACTION_UP:
                    Log.i("TAG", "touched up");
                    switch (v.getId()) {
                        case (R.id.LEFT):
                            LEFTheld = !LEFTheld;
                            break;
                        case (R.id.RIGHT):
                            RIGHTheld = !RIGHTheld;
                            break;
                        case (R.id.A):
                            Aheld = !Aheld;
                            break;
                        case (R.id.B):
                            Bheld = !Bheld;
                            break;
                        case (R.id.Z):
                            Zheld = !Zheld;
                            break;
                        case (R.id.CU):
                            CUheld = !CUheld;
                        case (R.id.CD):
                            CDheld = !CDheld;
                        case (R.id.CL):
                            CLheld = !CLheld;
                        case (R.id.CR):
                            CRheld = !CRheld;

                    }
            }
            return true;
        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controller);

        Joystick joystick = findViewById(R.id.joystick);
        joystick.setJoystickListener(new JoystickListener() {
            @Override
            public void onDown() {
                Log.i("joystick","onDown");
            }

            @Override
            public void onDrag(float degrees, float offset) {
                Log.i("joystick", "degrees: " + degrees + " and offset: " + offset);
                x = offset * cos(degrees);
                y = offset * sin(degrees);
                Log.i("joystick", "x: " + x + " and y: " + y);
            }

            @Override
            public void onUp() {
                Log.i("joystick", "onUp");
                x = 0 ;
                y = 0;
            }
        });

        findViewById(R.id.LEFT).setOnTouchListener(handleTouch);
        findViewById(R.id.RIGHT).setOnTouchListener(handleTouch);
        findViewById(R.id.A).setOnTouchListener(handleTouch);
        findViewById(R.id.B).setOnTouchListener(handleTouch);
        findViewById(R.id.CU).setOnTouchListener(handleTouch);
        findViewById(R.id.CD).setOnTouchListener(handleTouch);
        findViewById(R.id.CL).setOnTouchListener(handleTouch);
        findViewById(R.id.CR).setOnTouchListener(handleTouch);
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
                connected = true;


                out = new PrintWriter(new BufferedWriter(
                        new OutputStreamWriter(socket.getOutputStream())), true);

//                datastream = new DataOutputStream(socket.getOutputStream());

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

            while(connected) {
//                try {
//                    Thread.sleep(REFRESH_RATE); }
//                catch (Exception e) {
//                    e.printStackTrace(); }

                for (int i = 0; i < 9; i ++ ){
                    if (sad[i]){
                        out.print(1);
                    } else {
                        out.print(0);
                    }
                }
                out.print(Math.round(x*100.0)/100.0);
                out.println(Math.round(y*100.0)/100.0);

            }


        }

        //DataOutputStream

        public void talkToServer(PrintWriter stream) {
            try {
                Thread.sleep(REFRESH_RATE); }
            catch (Exception e) {
                e.printStackTrace(); }

            stream.print("helloworld");

//            try{
//                for (int i = 0; i < 11; i ++ ){
//                    if (sad[i]){
//                        stream.print(1);
//                    } else {
//                        stream.print(0);
//                    }
//                }
//                stream.print(Math.round(x*100.0)/100.0);
//                stream.print(Math.round(y*100.0)/100.0);
//
//                //stream.print(sad);
//                //stream.write(sad);
//                stream.flush(); }
////            catch (IOException e){
////                e.printStackTrace();
////                Log.i("error", "talk to server io exception"); }
//            catch (Exception e) {
//                e.printStackTrace();
//            }
//            output = default_op;

        }
    }

}
