## usage

```powershell
PS D:\workspace\QT\qt_idf\examples\opus_demo\build\build_out\target> .\opus_demo.exe -e voip 8000 1 8000 -cbr -bandwidth NB -complexity 0 -forcemono 1_RXAE.WAV speech_encoded.bit
libopus 1.3.1-160-g8cf872a1
Encoding 8000 Hz input at 8.000 kb/s in narrowband with 160-sample frames.
average bitrate:               8.000 kb/s
maximum bitrate:               8.000 kb/s
active bitrate:                8.000 kb/s
bitrate standard deviation:    0.000 kb/s

PS D:\workspace\QT\qt_idf\examples\opus_demo\build\build_out\target> .\opus_demo.exe -d 8000 1 speech_encoded.bit  1_out.wav
libopus 1.3.1-160-g8cf872a1
Decoding with 8000 Hz output (1 channels)
average bitrate:               8.000 kb/s
maximum bitrate:               8.000 kb/s
bitrate standard deviation:    0.000 kb/s
PS D:\workspace\QT\qt_idf\examples\opus_demo\build\build_out\target>
```

