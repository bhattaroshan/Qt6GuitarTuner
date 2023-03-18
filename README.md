# Qt6GuitarTuner
This is a guitar tuner app built with portaudio and cooley tukey in qt6. It also uses a custom Vumeter to help users set their guitar.



<img width="401" alt="test2" src="https://user-images.githubusercontent.com/4207226/226082040-70ffffe5-fbd9-4f74-aca5-ae0733dac898.png">

The app automatically detects the string you are trying to adjust by calculating the distance from generated frequency with standard string frequency. However the vumeter percentage is not done accurately. A bit of work is required to work on resolution.


<h1>Warning</h1>
<p>I've added absolute path for using portaudio. You might have to readjust CMAKE to load portaudio properly before you can compile the source</p>
