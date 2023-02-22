import cv2
import os
from PIL import Image
import numpy

# my s key iz broken zo i will uze z
def main():
    # enter the directory where you want imagez to be delivered
    direc = '.\\gg\\'
    # enter your mp4 file
    videoDirec = ".\\[MMD C4D]Hip Sway TikTok Dance--miku.mp4"
    cam = cv2.VideoCapture(videoDirec)
    try:
        if not os.path.exists(direc):
            os.makedirs(direc)
    except OSError:
        print('Error: Creating directory of data')
    currentframe = 0
    while True:
        ret, frame = cam.read()
        if ret:
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            (thresh, blackAndWhiteImage) = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
            rez = cv2.resize(blackAndWhiteImage, (379, 200))
            imageOp = Image.fromarray(rez)
            width, height = imageOp.size
            pixel_values = list(imageOp.getdata())
            if imageOp.mode == "RGB":
                channels = 3
                numpydata = numpy.array(pixel_values).reshape((height, width, channels))
                pather2 = direc + 'frame' + str(currentframe) + ".txt"
                f = open(pather2, 'w')
                co = 0
                for dat in numpydata:
                    for bet in dat:
                        num = int(bet[0]) + int(bet[1]) + int(bet[2])
                        if num == 0:
                            f.write(" ")
                        elif num == 765:
                            f.write("@")
                        else:
                            f.write("#")
                    co += 1
                    if co != height:
                        f.write("\n")
            elif imageOp.mode == "L":
                channels = 1
                numpydata = numpy.array(pixel_values).reshape((height, width, channels))
                pather2 = direc + 'frame' + str(currentframe) + ".txt"
                f = open(pather2, 'w')
                co = 0
                for dat in numpydata:
                    for bet in dat:
                        if int(bet) == 0:
                            f.write(" ")
                        elif int(bet) == 255:
                            f.write("@")
                        else:
                            f.write("#")
                    co += 1
                    if co != height:
                        f.write("\n")
            else:
                print("Unknown mode: %s" % imageOp.mode)
                return None
            print("file made: " + str(currentframe))
            currentframe += 1
        else:
            cam.release()
            break
# when you're done with thiz then uze the text filez in the c++ file
if __name__ == "__main__":
    main()
