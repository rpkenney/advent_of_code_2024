package main

import (
	"fmt"
	"os"
	"bufio"
	"strings"
	"strconv"
)

var rules = make(map[int][]int)

func addToRules(a int, b int){
	rules[a] = append(rules[a], b)
}


func compare(a int, b int) bool{
	//returns true if a should come before b
	rule := rules[a]

	for _, val := range(rule){
		if (b == val){
			return true
		}
	}
	return false
}

func quickSort(values []int) ([]int, bool){
	if(len(values) <= 1){
		return values, true
	}
	pivot := values[len(values) - 1]

	left := []int{}
	right := []int{}

	for _, val := range(values[:len(values) - 1]){
		if(compare(val, pivot)){
			left = append(left, val)
		} else {
			right = append(right, val)
		}
	}
	var changed bool
	left, changed = quickSort(left)
	right, _ = quickSort(right)

	right = append([]int{pivot}, right...)
	return append(left, right...), (len(left) == len(values) - 1 && changed)

}

func main() {

	filename := "../inputs/day5.txt"

	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Failed to open file:", err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)

	rulesSection := true
	sum := 0
	for scanner.Scan() {
		line := scanner.Text()
		if(len(line) == 0){
			rulesSection = false
			continue
		}
		if(rulesSection){
			values := strings.Split(line, "|")
			a, _ := strconv.Atoi(strings.TrimSpace(values[0]))
			b, _ := strconv.Atoi(strings.TrimSpace(values[1]))
			addToRules(a, b)
		} else {
			values := strings.Split(line, ",")
			numbers := []int{}
			for _, value := range values {
				num, _ := strconv.Atoi(strings.TrimSpace(value))
				numbers = append(numbers, num)
			}

			sorted, changed := quickSort(numbers)
			if(!changed){
				sum += sorted[len(sorted) / 2]
			}
		}
	}

	fmt.Println(sum)
}
