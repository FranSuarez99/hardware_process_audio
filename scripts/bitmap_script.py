import logging
import psutil
import win32ui
import win32gui
import win32con
import win32api

# Setup logging
LOG_FILENAME = 'bitmap_script.log'
logging.basicConfig(
    level=logging.ERROR,
    format='%(asctime)s - %(levelname)s - %(message)s',
    filename=LOG_FILENAME
)
logger = logging.getLogger()

def get_process_icons():
    process_icons = {}

    # Iterate over all running processes
    for proc in psutil.process_iter(['pid', 'name']):
        try:
            # Get process handle
            handle = win32gui.GetForegroundWindow()
            # Get process icon
            icon = win32gui.ExtractIcon(win32api.GetModuleHandle(None), proc.info['name'], 0)
            if icon:
                # Convert icon to bitmap
                icon_bitmap = win32ui.CreateBitmap()
                icon_bitmap.CreateCompatibleBitmap(win32gui.GetDC(0), 32, 32)
                dc = win32ui.CreateDC()
                dc.SelectObject(icon_bitmap)
                dc.DrawIcon((0, 0), icon[0])
                # Save bitmap to file
                bitmap_path = f"{proc.info['name']}.bmp"
                icon_bitmap.SaveBitmapFile(dc, bitmap_path)
                # Close handles
                dc.DeleteDC()
                icon_bitmap.DeleteObject()
                win32gui.DestroyIcon(icon[0])
                # Store bitmap path
                process_icons[proc.info['name']] = bitmap_path
        except win32gui.error as e:
            # Log error and continue to the next process
            logger.error(f"Error retrieving icon for {proc.info['name']}: {e}")
        except Exception as e:
            # Log other exceptions and continue to the next process
            logger.error(f"Error retrieving icon for {proc.info['name']}: {e}")

    return process_icons

def main():
    process_icons = get_process_icons()
    print("Process icons saved successfully.")

if __name__ == "__main__":
    main()
