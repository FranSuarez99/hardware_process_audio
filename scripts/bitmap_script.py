import logging
import psutil
import win32ui
import win32gui
import win32con
import win32api
from PIL import Image

# Setup logging
LOG_FILENAME = 'scripts\\log\\bitmap_script.log'
logging.basicConfig(
    level=logging.ERROR,
    format='%(asctime)s - %(levelname)s - %(message)s',
    filename=LOG_FILENAME
)
logger = logging.getLogger()

def get_icon_from_process(proc: psutil.Process) -> None:
    path = proc.exe().replace("\\", "/")
    icoX = win32api.GetSystemMetrics(win32con.SM_CXICON)
    icoY = win32api.GetSystemMetrics(win32con.SM_CXICON)

    large, small = win32gui.ExtractIconEx(path, 0)
    win32gui.DestroyIcon(small[0])

    hdc = win32ui.CreateDCFromHandle(win32gui.GetDC(0))
    hbmp = win32ui.CreateBitmap()
    hbmp.CreateCompatibleBitmap(hdc, icoX, icoX)
    hdc = hdc.CreateCompatibleDC()

    hdc.SelectObject(hbmp)
    hdc.DrawIcon((0,0), large[0])

    bmpstr = hbmp.GetBitmapBits(True)
    img = Image.frombuffer(
        'RGBA',
        (32,32),
        bmpstr, 'raw', 'BGRA', 0, 1
    )
    monochrome_img = img.convert('1')
    monochrome_img.save(f'icons\\{proc.name()[:-4]}.bmp')

def get_process_icons() -> None:
    for proc in psutil.process_iter():
        try:
            if proc.exe():
                    get_icon_from_process(proc)
            else:
                pass
        except Exception as e:
            # Log other exceptions and continue to the next process
            logger.error(f"Error retrieving icon for {proc.name()}, PID {proc.pid}: {e}")

def main():
    get_process_icons()
    print("Process icons saved successfully.")

if __name__ == "__main__":
    main()
