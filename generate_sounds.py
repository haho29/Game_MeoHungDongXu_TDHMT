import wave
import math
import struct
import random
import os
import shutil

SAMPLE_RATE = 44100

def save_wav(filename, data):
    with wave.open(filename, 'wb') as w:
        w.setnchannels(1)  # Mono
        w.setsampwidth(2)  # 16-bit PCM
        w.setframerate(SAMPLE_RATE)
        for val in data:
            # Clamp to 16-bit signed integer range
            val = max(-32768, min(32767, int(val)))
            w.writeframesraw(struct.pack('<h', val))

def scale_wav_volume(src_filename, dest_filename, factor):
    try:
        with wave.open(src_filename, 'rb') as w_in:
            params = w_in.getparams()
            n_channels = params.nchannels
            sampwidth = params.sampwidth
            framerate = params.framerate
            n_frames = params.nframes
            
            data = w_in.readframes(n_frames)
            
        if sampwidth == 2:
            fmt = f"<{len(data)//2}h"
            samples = list(struct.unpack(fmt, data))
            scaled_samples = [int(max(-32768, min(32767, s * factor))) for s in samples]
            new_data = struct.pack(fmt, *scaled_samples)
        elif sampwidth == 1:
            fmt = f"<{len(data)}B"
            samples = list(struct.unpack(fmt, data))
            scaled_samples = [int(max(0, min(255, 128 + (s - 128) * factor))) for s in samples]
            new_data = struct.pack(fmt, *scaled_samples)
        else:
            print(f"Unsupported sample width {sampwidth} for {src_filename}")
            return False
            
        with wave.open(dest_filename, 'wb') as w_out:
            w_out.setparams(params)
            w_out.writeframes(new_data)
        print(f"Volume of {src_filename} scaled by {factor} and saved to {dest_filename}")
        return True
    except Exception as e:
        print(f"Error scaling volume from {src_filename} to {dest_filename}: {e}")
        return False

# LOUDER Synthesized Sounds:
def gen_bomb():
    data = []
    duration = 0.5
    n_samples = int(SAMPLE_RATE * duration)
    
    for i in range(n_samples):
        t = i / SAMPLE_RATE
        ratio = t / duration
        
        # Low rumble sweep
        freq = 150 * (1.0 - ratio)
        sine = math.sin(2 * math.pi * freq * t)
        
        # Crackly explosion noise
        noise = random.uniform(-1.0, 1.0)
        
        # Mix mostly noise (80%) and low sine rumble (20%)
        mix = 0.8 * noise + 0.2 * sine
        
        # Exponential decay envelope
        env = math.exp(-4.5 * ratio)
        
        # INCREASED volume from 14000 to 25000 (Very Loud!)
        val = 25000 * mix * env
        data.append(val)
        
    return data

def gen_bone():
    data = []
    duration = 0.25
    n_samples = int(SAMPLE_RATE * duration)
    
    for i in range(n_samples):
        t = i / SAMPLE_RATE
        # Descending frequency from 300 to 80 Hz
        freq = 300 - 220 * (t / duration)
        # Use square wave for 8-bit buzzy retro feel
        sine = math.sin(2 * math.pi * freq * t)
        # INCREASED volume from 8000 to 18000 (Much Louder!)
        square = 18000 if sine >= 0 else -18000
        env = 1.0 - (t / duration)
        data.append(square * env)
        
    return data

def gen_heal():
    data = []
    # 4 notes arpeggio: C5(523.25), E5(659.25), G5(783.99), C6(1046.50)
    notes = [523.25, 659.25, 783.99, 1046.50]
    note_duration = 0.08
    n_samples = int(SAMPLE_RATE * note_duration)
    
    for note_idx, freq in enumerate(notes):
        for i in range(n_samples):
            t = i / SAMPLE_RATE
            env = math.exp(-3 * t)
            # INCREASED volume from 10000 to 20000 (Very Loud!)
            val = 20000 * math.sin(2 * math.pi * freq * t) * env
            data.append(val)
            
    return data

def gen_shield_up():
    data = []
    duration = 0.4
    n_samples = int(SAMPLE_RATE * duration)
    
    for i in range(n_samples):
        t = i / SAMPLE_RATE
        # Exponential frequency sweep from 250 Hz to 1800 Hz
        ratio = t / duration
        freq = 250 * (7.2 ** ratio)
        # Smooth sine sweep
        # INCREASED volume from 10000 to 20000 (Very Loud!)
        val = 20000 * math.sin(2 * math.pi * freq * t)
        # Fade in and fade out envelope
        if ratio < 0.1:
            env = ratio / 0.1
        else:
            env = 1.0 - (ratio - 0.1) / 0.9
        data.append(val * env)
        
    return data

def gen_shield_break():
    data = []
    duration = 0.35
    n_samples = int(SAMPLE_RATE * duration)
    
    for i in range(n_samples):
        t = i / SAMPLE_RATE
        ratio = t / duration
        # Descending sweep combined with noise
        freq = 600 - 500 * ratio
        sine = math.sin(2 * math.pi * freq * t)
        
        # Noise component for shatter effect
        noise = random.uniform(-1, 1)
        
        # Mix 60% noise and 40% sine wave for a crunchy explosion
        mix = 0.4 * sine + 0.6 * noise
        env = math.exp(-5 * ratio)
        
        # INCREASED volume from 12000 to 23000 (Very Loud!)
        val = 23000 * mix * env
        data.append(val)
        
    return data

if __name__ == '__main__':
    # 1. Generate Loud Custom Retro Sound Effects
    save_wav('bomb.wav', gen_bomb())
    save_wav('bone.wav', gen_bone())
    save_wav('heal.wav', gen_heal())
    save_wav('shield_up.wav', gen_shield_up())
    save_wav('shield_break.wav', gen_shield_break())
    print("Louder synthesized sound effects generated successfully!")
    
    # 2. Automatically Scale Background Music (nhacnen.wav) safely
    music_path = 'nhacnen.wav'
    backup_path = 'nhacnen_backup.wav'
    
    if os.path.exists(music_path):
        if not os.path.exists(backup_path):
            print("Creating backup of original background music...")
            shutil.copyfile(music_path, backup_path)
            print("Backup created successfully.")
        
        # Scale music down to 30% volume
        print("Reducing volume of background music to 30%...")
        scale_wav_volume(backup_path, music_path, 0.30)
        print("Background music volume adjusted successfully!")
    else:
        print("Warning: nhacnen.wav not found, skipping volume adjustment.")
