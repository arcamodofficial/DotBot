package com.imgui.arcamod;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.imgui.arcamod.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'arcamod' library on application startup.
    static {
        System.loadLibrary("arcamod");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'arcamod' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}