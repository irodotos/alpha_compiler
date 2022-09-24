#!/bin/sh

# cat ours | tr -d "│" |  sed "1,3d"| sed -r "s/\_f/\$/g" | sed -r "s/\_t/^/g" |sed -r "s/^#([0-9]+)(.*)/\1:\2/g" | sed -r "s/\s+/ /g" | sed -r "s/TRUE/'\L&'/g" | sed -r "s/FALSE/'\L&'/g"

ours="$(cat ours | sed -r "s/│//g" \
	 | sed "1,3d" \
	 | sed -r "s/\_f/\$/g" \
	 | sed -r "s/\_t/^/g" \
	 | sed -r "s/^#([0-9]+)(.*)/\1:\2/g" \
	 | sed -r "s/\s+/ /g" \
	 | sed -r "s/TRUE/'\L&'/g" \
	 | sed -r "s/FALSE/'\L&'/g" \
 	 | sed -r "s/[0-9]+$//g"
	 )"

okeanos="$(cat "$1" | sed -r "s/\[.*\]//g" | sed -r "s/IGNORE QUAD//g")"
echo "${ours}" > _ours
echo "${okeanos}" > _okeanos
diff _ours _okeanos --color --ignore-all-space -s
rm _ours _okeanos
