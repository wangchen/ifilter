#ifilter

Command line tool to filter image by dimensions

## Usage

	find ~/Pictures |./ifilter -w ${width} -h ${height}

The width and height could be:

- `-1024` - **greater than** 1024 break
- `+1024` - **less than** 1024 pixels
- `1024` - **equals to** 1024 pixels

The width and height are both optional. If nothing specified ifilter do nothing.