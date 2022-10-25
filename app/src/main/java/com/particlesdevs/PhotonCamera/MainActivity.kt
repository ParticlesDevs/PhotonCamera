package com.particlesdevs.PhotonCamera

import android.app.NativeActivity
import android.os.Bundle
import android.content.Context
import android.view.inputmethod.InputMethodManager
import android.view.KeyEvent
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.util.concurrent.LinkedBlockingQueue

class MainActivity : NativeActivity() {
    lateinit var nativeBuffer: ByteBuffer
    public override fun onCreate(savedInstanceState: Bundle?) {
        nativeBuffer = ByteBuffer.allocateDirect(32*4);
        nativeBuffer.position(0)
        nativeBuffer.order(ByteOrder.nativeOrder())
        super.onCreate(savedInstanceState)
    }

    fun showSoftInput() {
        val inputMethodManager = getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        inputMethodManager.showSoftInput(this.window.decorView, 0)
    }

    fun hideSoftInput() {
        val inputMethodManager = getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        inputMethodManager.hideSoftInputFromWindow(this.window.decorView.windowToken, 0)
    }

    // Queue for the Unicode characters to be polled from native code (via pollUnicodeChar())
    private var unicodeCharacterQueue: LinkedBlockingQueue<Int> = LinkedBlockingQueue()

    // We assume dispatchKeyEvent() of the NativeActivity is actually called for every
    // KeyEvent and not consumed by any View before it reaches here
    override fun dispatchKeyEvent(event: KeyEvent): Boolean {
        nativeBuffer.position(4)
        nativeBuffer.putInt(0)
        val pos = nativeBuffer.get(0).toInt()
        nativeBuffer.position(pos*4 + 8)
        if (event.action == KeyEvent.ACTION_DOWN) {
            nativeBuffer.putInt(event.getUnicodeChar(event.metaState))
            //unicodeCharacterQueue.offer(event.getUnicodeChar(event.metaState))
        }
        nativeBuffer.position(0)
        nativeBuffer.putInt(pos+1)
        nativeBuffer.putInt(1)

        return super.dispatchKeyEvent(event)
    }
    fun getUnicodeByteBuffer(): ByteBuffer {
        return nativeBuffer
    }

    //fun pollUnicodeChar(): Int {
    //    return unicodeCharacterQueue.poll() ?: 0
    //}
}
