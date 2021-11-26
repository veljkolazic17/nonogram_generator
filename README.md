# nonogram_generator
## How to use it:
After compiling the *genon.c* you can run program from console like this:
*for windows cmd*
```powershell
PS Users\veljk\nonogram_generator> cmd /c genon.exe PATH_IN SIZE PATH_OUT SENSITIVITY
```
## Parameters
* **PATH_IN** &rarr; path to an image you watn to transform
* **SIZE** &rarr; number of pixels in rows and columns
* **PATH_OUT** &rarr; path where you want to store a generated image
* **SENSITIVITY** &rarr; should tweak(for smaller image with brighter colours you shoud put higher sensitivity)
## Example:
```powershell
PS Users\veljk\nonogram_generator> cmd /c genon.exe "psc.png" 40 "done.png" 220
```
### **psc.png**
![](https://github.com/veljkolazic17/nonogram_generator/blob/main/testimage/psc.png)
### **done.png**
![](https://github.com/veljkolazic17/nonogram_generator/blob/main/testimage/done1.png)
```powershell
PS Users\veljk\nonogram_generator> cmd /c genon.exe "pika.png" 20 "done2.png" 220
```
### **psc.png**
![](https://github.com/veljkolazic17/nonogram_generator/blob/main/testimage/pika.png)
### **done.png**
![](https://github.com/veljkolazic17/nonogram_generator/blob/main/testimage/done2.png)
