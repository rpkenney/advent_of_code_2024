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

  //left right
  for(let j = 0; j < crossword.length; j++){
    row = ""
    for(let i = 0; i < crossword[0].length; i++){
        row += crossword[j][i];
    }
    count += row.split('XMAS').length - 1;
    count += row.split('SAMX').length - 1;
  }

  //up down
  for(let i = 0; i < crossword[0].length; i++){
    col = ""
    for(let j = 0; j < crossword.length; j++){
        col += crossword[j][i];
    }
    count += col.split('XMAS').length - 1;
    count += col.split('SAMX').length - 1;
  }

  //diagonal down left
  for(let i = 0; i < crossword[0].length; i++){
    let col = i, row = 0;
    diag = ""
    while(row < crossword.length && col < crossword[0].length){
        diag += crossword[row][col]
        row++
        col++
    }
    count += diag.split('XMAS').length - 1;
    count += diag.split('SAMX').length - 1;
  }

  for(let i = 1; i < crossword.length; i++){
    let col = 0, row = i;
    diag = ""
    while(row < crossword.length && col < crossword[0].length){
        diag += crossword[row][col]
        row++
        col++
    }
    count += diag.split('XMAS').length - 1;
    count += diag.split('SAMX').length - 1;
  }
  //diagonal up left
  for(let i = 0; i < crossword[0].length; i++){
    let col = i, row = crossword.length - 1;
    diag = ""
    while(row >= 0 && col < crossword[0].length){
        diag += crossword[row][col]
        row--
        col++
    }
    count += diag.split('XMAS').length - 1;
    count += diag.split('SAMX').length - 1;
  }

  for(let i = crossword.length - 2; i >= 0; i--){
    let col = 0, row = i;
    diag = ""
    while(row >= 0 && col < crossword[0].length){
        diag += crossword[row][col]
        row--
        col++
    }
    count += diag.split('XMAS').length - 1;
    count += diag.split('SAMX').length - 1;
  }

  console.log(count)
} catch (err) {
  console.error(err);
}