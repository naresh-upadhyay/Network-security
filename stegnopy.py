from PIL import Image
import stepic as crypto

ch = input("Enter Encryption/Decryption [e/d]:-")
while(1):
    if(ch == 'e' or ch == 'E'):
        txt = input("Enter text to encrypt :-")
        imgf = input("\nEnter image file name :-")
        img = Image.open(imgf)
        textbyte = bytes(txt,"utf-8")
        encodeimg = crypto.encode(img,textbyte)
        encodeimg.save(imgf,'PNG')
        newimg = Image.open(imgf)
        img.show()
        newimg.show()
    elif(ch == 'd' or ch == 'D'):
        ip = input("\nEnter the image file name: ")
        im = Image.open(ip)
        text = crypto.decode(im)
        print("\nDecoded Text: ", text)
    else:
        break
    ch = input("Enter Encryption/Decryption [e/d]:-")
