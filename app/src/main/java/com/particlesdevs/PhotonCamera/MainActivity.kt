package com.particlesdevs.PhotonCamera

import android.app.NativeActivity
import android.os.Bundle
import android.content.Context
import android.content.pm.PackageManager
import android.graphics.SurfaceTexture
import android.os.Build
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.util.LogPrinter
import android.view.inputmethod.InputMethodManager
import android.view.KeyEvent
import android.view.Surface
import android.widget.Toast
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.util.concurrent.LinkedBlockingQueue
import kotlin.system.exitProcess

class MainActivity : NativeActivity() {
    lateinit var nativeBuffer: ByteBuffer
    lateinit var s: SurfaceTexture
    var updateSurface = false
    lateinit var mHandler: Handler
    public override fun onCreate(savedInstanceState: Bundle?) {
        //Load library symbols with native glue
        System.loadLibrary("NPhotonCamera")
        nativeBuffer = ByteBuffer.allocateDirect(32*4);
        nativeBuffer.position(0)
        nativeBuffer.order(ByteOrder.nativeOrder())
        while(checkSelfPermission(android.Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED){
            requestPermissions(arrayOf(android.Manifest.permission.CAMERA), 1)
        }
        super.onCreate(savedInstanceState)
    }
    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == 1 && grantResults.size > 0
            && grantResults?.get(0) != PackageManager.PERMISSION_GRANTED) {
            Toast.makeText(this, "This app requires camera permission", Toast.LENGTH_SHORT).show()
            finish()
        }
    }
    override fun onResume() {
        super.onResume()
    }

    override fun onDestroy() {
        super.onDestroy()
        s.release()
    }

    //Used by JNI
    fun showSoftInput() {
        val inputMethodManager = getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        inputMethodManager.showSoftInput(this.window.decorView, 0)
    }

    //Used by JNI
    fun hideSoftInput() {
        val inputMethodManager = getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        inputMethodManager.hideSoftInputFromWindow(this.window.decorView.windowToken, 0)
    }

    // We assume dispatchKeyEvent() of the NativeActivity is actually called for every
    // KeyEvent and not consumed by any View before it reaches here
    override fun dispatchKeyEvent(event: KeyEvent): Boolean {
        nativeBuffer.position(4)
        nativeBuffer.putInt(0)
        val pos = nativeBuffer.get(0).toInt()
        nativeBuffer.position(pos*4 + 8)
        if (event.action == KeyEvent.ACTION_DOWN) {
            nativeBuffer.putInt(event.getUnicodeChar(event.metaState))
        }
        nativeBuffer.position(0)
        nativeBuffer.putInt(pos+1)
        nativeBuffer.putInt(1)

        return super.dispatchKeyEvent(event)
    }
    fun getUnicodeByteBuffer(): ByteBuffer {
        return nativeBuffer
    }
    //Used by JNI
    fun updateTexImage(){
        s.updateTexImage()
    }

    fun closeMain(){
        exitProcess(1)
    }
    private external fun onImageAvailable()
    fun getSurfaceTexture(id: Int, width: Int,height: Int): Surface {
        s = SurfaceTexture(id)
        s.setDefaultBufferSize(width,height)
        s.setOnFrameAvailableListener {
            onImageAvailable()
        }

        return Surface(s)
    }
}
