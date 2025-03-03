#! /usr/bin/python

from sys import stderr, exit
from argparse import ArgumentParser


def failed_import(pkg):
	print(f'Please install {pkg}', file=stderr)
	exit(1)

try:
	from PIL import Image
except:
	failed_import('python-pillow')
try:
	import numpy as np
except:
	failed_import('python-numpy')

try:
	import serial
except:
	failed_import('python-pyserial')


def collapse_column(col):
	return sum([x << i for i, x in enumerate(col)])

def make_scrolling_img(img):
	size = (img.shape[1] if img.shape[1] <= 0x300 else 0x300) - 1
	payload = np.empty(size + 5, dtype=np.uint8)
	payload[0] = 0x46
	payload[1] = size >> 8
	payload[2] = size & 0xff
	for i in range(size + 1):
		payload[i+3] = collapse_column(img[:,i])

	payload[-1] = (1 + ~np.sum(payload[1:-1])) & 0xff

	return payload
		

def main(args):
	with Image.open(args.image) as img:
		img = img.convert('1')
		if args.invert:
			pass
		if img.height > 8 and args.no_trim_image:
			new_width = img.width * 8 // img.height
			img = img.resize((new_width, 8), resample = Image.Resampling.NEAREST)
		elif img.height > 8:
			print('[W] cropping image')
			img = img.crop((0, 0, 8, img.width))
		img = np.array(img)

	payload = make_scrolling_img(img).tobytes('C')

	if args.verbose: print(f'[I] generated payload: {payload}')

	with serial.Serial(args.port, args.baud) as ser:
		ret = ser.write(payload)

	if ret != len(payload):
		print('[E] payload was not completely written\n'
				f'    only {ret} bytes written')

	if args.verbose: print(f'[I] done')
	

if __name__ == "__main__":
	parser = ArgumentParser()
	argument_list = [
			[ '--port', { 'default': '/dev/ttyACM0', 'type': str } ],
			[ '--baud', { 'default': 115200, 'type': int } ],
			# [ '--rotate', { 'default': False, 'action': 'store_true' } ],
			[ '--no-trim-image', { 'default': False, 'action': 'store_true' } ],
			[ '--verbose', { 'default': False, 'action': 'store_true' } ],
			[ 'image', { 'type': str, 'default': 'test-imgs/helloworld.png' } ]
		]

	for arg, data in argument_list:
		parser.add_argument(arg, **data)

	main(parser.parse_args())
