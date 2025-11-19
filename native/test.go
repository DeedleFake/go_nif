package main

/*
#cgo CFLAGS: -I/usr/lib/erlang/usr/include
*/
import "C"
import (
	"io"
	"net/http"
	"strings"
)

//export get
func get(url *C.char) (*C.char, *C.char) {
	rsp, err := http.Get(C.GoString(url))
	if err != nil {
		return nil, C.CString(err.Error())
	}
	defer rsp.Body.Close()

	var buf strings.Builder
	_, err = io.Copy(&buf, rsp.Body)
	if err != nil {
		return nil, C.CString(err.Error())
	}

	return C.CString(buf.String()), nil
}

func main() {
}
