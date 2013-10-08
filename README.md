#ifilter

Command line tool to filter image by dimensions

## Usage

	find ~/Pictures |./ifilter -w ${width} -h ${height}

The width and height can be positive or negative.
- Positive - 'greater than'
- Negative - 'less than'

The width and height are both optional. If nothing specified ifilter do nothing.