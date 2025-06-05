package com.particlesdevs.PhotonCamera

import android.app.NativeActivity
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.graphics.SurfaceTexture
import android.net.Uri
import android.os.Build
import android.os.Build.VERSION
import android.os.Bundle
import android.os.Environment
import android.os.Handler
import android.provider.Settings
import android.view.KeyEvent
import android.view.Surface
import android.view.inputmethod.InputMethodManager
import android.widget.Toast
import androidx.annotation.RequiresApi
import java.nio.ByteBuffer
import java.nio.ByteOrder
import kotlin.system.exitProcess

class MainActivity : NativeActivity() {
    lateinit var nativeBuffer: ByteBuffer
    lateinit var s: SurfaceTexture
    lateinit var surf: Surface
    var updateSurface = false
    lateinit var mHandler: Handler
    lateinit var context: Context
    public override fun onCreate(savedInstanceState: Bundle?) {
        context = applicationContext
        //Load library symbols with native glue
        System.loadLibrary("NPhotonCamera")
        nativeBuffer = ByteBuffer.allocateDirect(32*4);
        nativeBuffer.position(0)
        nativeBuffer.order(ByteOrder.nativeOrder())
        while(checkSelfPermission(android.Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED){
            requestPermissions(arrayOf(android.Manifest.permission.CAMERA), 1)
        }
        /*while(checkSelfPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            requestPermissions(arrayOf(android.Manifest.permission.WRITE_EXTERNAL_STORAGE), 1)
        }*/

        if (VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            val uri = Uri.parse("package:${BuildConfig.APPLICATION_ID}")
            if(!hasAllFilesPermission())
                startActivity(
                Intent(
                    Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION,
                    uri
                )
                )
        } else {
            //below android 11
            while(checkSelfPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
                requestPermissions(arrayOf(android.Manifest.permission.WRITE_EXTERNAL_STORAGE), 2)
            }
        }
        super.onCreate(savedInstanceState)
    }
    @RequiresApi(Build.VERSION_CODES.R)
    private fun hasAllFilesPermission() = Environment.isExternalStorageManager()

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

    fun pressBack() {
        super.onBackPressed()
    }

    override fun onBackPressed() {

        //super.onBackPressed()
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
    fun getName(): String {
        return packageName
    }
    fun getCache(): String {
        return cacheDir.absolutePath
    }
    fun Camera2APIInit(){

    }
    fun setCamera2APIPreview(){

    }
    fun Camera2APIReInit(){

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
        surf = Surface(s)
        return surf
    }
}
