package com.example.androidapp_unicon;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;



import android.view.View;


public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    }

    public void onGameCube(View view) {
        Intent intent = new Intent(this, ControllerActivity.class);
        startActivity(intent);
    }


//    public void onClick(View view) {
//        Log.i("onclick", "click method calling");
//
//        EditText et = (EditText) findViewById(R.id.EditText01);
//        output = et.getText().toString();
//        Log.i("onclick", "Sent: " + output);
//
//    }

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

