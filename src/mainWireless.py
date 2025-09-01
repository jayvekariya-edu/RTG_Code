import cv2 as cv
from ultralytics import YOLO
import time
# import serial

# port = "/dev/ttyUSB0"
# baud = 9600
# esp = serial.Serial(port, baud, timeout=1)

# import serial

# ser = serial.Serial()
# ser.baudrate = 115200
# ser.port = 'COM3'
# ser.open()

import websocket
import time

ESP32_IP = "ipaddress"  # replace with your ESP32 IP
ws = websocket.WebSocket()
ws.connect(f"ws://{ESP32_IP}:81")

def analog_write(pin, value):
    msg = f"PIN:{pin}:{value}"
    ws.send(msg)
    # reply = ws.recv()
    # print("ESP32:", reply)

model = YOLO("best.pt")
class_names = ["dislike", "fist", "one", "peace", "stop", "no_gesture"]
org = (70, 70)
font = cv.FONT_HERSHEY_COMPLEX
font_scale = 1.5
color = (0, 255, 0)
thickness = 2
line_type = cv.LINE_AA
camera=cv.VideoCapture(0)

while True:
    start_time = time.time()
    ret, frame = camera.read()
    if not ret:
        break
    result=model(frame, conf=0.5, verbose=False)
    processed_frame = result[0].plot()
    boxes = result[0].boxes
    speed = result[0].speed
    max_conf=0
    cls=5
    for box in boxes:
        if(box.conf[0]>max_conf):
            max_conf=float(box.conf[0])
            cls=int(box.cls[0])
        cls_id = int(box.cls[0])        
        conf = float(box.conf[0]) 

        # print("Detected_classID:", cls_id)
        # label = class_names[cls_id]
        # print("Label:", label)

    end_time = time.time()
    elapsed_ms = (end_time - start_time) * 1000
    fps = int(1000 / elapsed_ms if elapsed_ms > 0 else 0)
    cv.putText(processed_frame, f"FPS:{str(fps)}", org, font, font_scale, color, thickness, line_type)
    cv.imshow("testingYolo",processed_frame)
    motion=class_names[cls]+"\n"
    # ser.write(motion.encode('utf=8'))
    ws.send(motion)
    
    # line = ser.readline().decode('utf-8')
    # print(line,end="")

    # if esp.in_waiting > 0:
    #     line = esp.readline().decode('utf-8').strip()
    #     print("esp says:", line)
    if cv.waitKey(1) & 0xFF == ord("x"):
        break
ws.close()
camera.release()

cv.destroyAllWindows()
