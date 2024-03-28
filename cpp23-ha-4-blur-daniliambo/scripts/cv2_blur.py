import argparse
import cv2


def blur(image_src, radius):
    x, y = radius // 2, radius // 2
    width, height = image_src.shape[:2]
    blured_image = cv2.GaussianBlur(src=image_src, ksize=(radius, radius), sigmaX=0, sigmaY=0)
    image_src[x:width - x, y:height - y] = blured_image[x:width - x, y:height - y]
    return image_src


def _main():
    parser = argparse.ArgumentParser(description='Test blur images with OpenCV.')
    parser.add_argument('-i', '--input', required=True, type=str, help='Input image.')
    parser.add_argument('-o', '--output', required=True, type=str, help='Output image.')
    parser.add_argument('-r', '--radius', required=True, type=int, help='Filter radius.')

    args = parser.parse_args()

    src_image = cv2.imread(args.input, cv2.BORDER_DEFAULT)
    dst_image = blur(src_image, args.radius)
    cv2.imwrite(args.output, dst_image)


if __name__ == '__main__':
    exit(_main())
