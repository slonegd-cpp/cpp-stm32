package main

import (
	"fmt"
	"io/ioutil"
	"os"
)

func main() {
	file, _ := os.Open("a.bin")
	bytes, _ := ioutil.ReadAll(file)
	for i := 0; i < len(bytes); i += 4 {
		fmt.Printf("% X\n", bytes[i:i+4])
	}
}
