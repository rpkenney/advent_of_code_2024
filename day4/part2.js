const fs = require('fs');

try {
  const data = fs.readFileSync('../inputs/day4.txt', 'utf8');

  var crossword = []
  var j = 0;
  crossword[j] = []

  for(let i = 0; i < data.length; i++){
    if(data[i] == '\n'){
        j++
        crossword[j] = []
    } else if ('XMAS'.includes(data[i])){
        crossword[j].push(data[i])
    }
  }
  count = 0

  let numCols = crossword[0].length
  let numRows = crossword.length

  for(let j = 1; j < numRows - 1; j++){
    for(let i = 1; i < numCols - 1; i++){
        if(crossword[j][i] == 'A'){
            str1 = crossword[j - 1][i - 1] + crossword[j + 1][i + 1]
            str2 = crossword[j + 1][i - 1] + crossword[j - 1][i + 1]

            if((str1 == 'MS' || str1 == 'SM') && (str2 == 'MS' || str2 == 'SM')){
                count++
            }
        }
    }
  }

  console.log(count)
} catch (err) {
  console.error(err);
}