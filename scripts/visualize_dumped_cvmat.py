import cv2
import argparse
import matplotlib.pyplot as plt
from pathlib import Path


SCRIPT_DIR = str(Path(__file__).parent)


def parse_args():
    parser = argparse.ArgumentParser(description="visualize cv::Mat dumped with .xml (cv::FileStorage)")
    parser.add_argument("--input-xml", "-i", type=str, default=f"{SCRIPT_DIR}/../output/curvature.xml")
    return parser.parse_args()


def main(input_xml):
    cv_file = cv2.FileStorage(input_xml, cv2.FILE_STORAGE_READ)
    image_curvature = cv_file.getNode("mat").mat()
    imgplot = plt.imshow(image_curvature)
    imgplot.set_cmap("nipy_spectral")
    #plt.show()
    plt.savefig("../curvature.png")

if __name__ == "__main__":
    args = parse_args()
    main(args.input_xml)