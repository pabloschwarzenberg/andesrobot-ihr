import cv2

def test_camera():
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("Could not open webcam")
        return

    print("q to quit")
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Capture failed",ret,frame)
            break

        cv2.imshow("Camera feed",frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        cap.release()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    test_camera()
