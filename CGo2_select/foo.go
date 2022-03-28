package main

import "C"
import (
	"fmt"
	"os"
	"unsafe"

	"github.com/liamg/flinch/widgets"
)

var (
	CANCEL_STRING = "<NONE>"
	max_attempts  = 3
	title         = "Select an environment"
	options       = []string{
		"Development",
		"Test",
		"Staging",
		"Production",
	}
)

func main() {}

/*
 * void -> bool
 */
//export do_confirm
func do_confirm() bool {
	confirmed, err := widgets.Confirm("Are you sure?")
	if err != nil {
		panic(err)
	}

	fmt.Printf("Confirmed: %d\n", confirmed)
	return confirmed
}

/*
 * void -> string
 */
//export do_input
func do_input() uintptr {
	name, err := widgets.Input("Enter your email...")
	if err == widgets.ErrInputCancelled {
		fmt.Println("User cancelled.")
		buf := []byte(fmt.Sprintf("%s", CANCEL_STRING))
		return uintptr(unsafe.Pointer(&buf[0]))
	}
	if len(name) < 1 {
		name = CANCEL_STRING
	}
	buf := []byte(fmt.Sprintf("%s", name))
	fmt.Fprintf(os.Stderr, "%s", buf)

	return uintptr(unsafe.Pointer(&buf[0]))
}

/*
 * void -> string
 */
//export do_select
func do_select() uintptr {
	_, item, err := widgets.ListSelect(title, options)
	if err == widgets.ErrInputCancelled {
		buf := []byte(fmt.Sprintf("%s", CANCEL_STRING))
		return uintptr(unsafe.Pointer(&buf[0]))
	}

	buf := []byte(fmt.Sprintf("%s", item))
	fmt.Fprintf(os.Stderr, "%s", buf)

	return uintptr(unsafe.Pointer(&buf[0]))
}

/*
 * void -> string
 */
//export do_password
func do_password() uintptr {
	var attempts = 0
	var pass string
	for {
		_pass, err := widgets.PasswordInput(fmt.Sprintf("Enter your password :: Attempt %d/%d", attempts+1, max_attempts))
		if err == widgets.ErrInputCancelled {
			fmt.Println("User cancelled.")
			os.Exit(1)
		}

		if len(_pass) > 0 {
			pass = _pass
			break
		} else {
			attempts++
			if attempts >= max_attempts {
				os.Exit(1)
			}
		}
	}

	fmt.Printf("Validating Password, %s!\n", pass)
	buf := []byte(fmt.Sprintf("%s", pass))
	fmt.Fprintf(os.Stderr, "password: %s\n", buf)
	if len(string(buf)) < 1 {
		buf = []byte(CANCEL_STRING)
	}
	return uintptr(unsafe.Pointer(&buf[0]))
}
