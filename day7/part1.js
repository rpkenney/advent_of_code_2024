const fs = require('fs');

function descend(parent, remaining, target) {
    if(remaining.length == 0){
        if(parent == target){
            return true
        } else {
            return false
        }
    }

    var option1 = descend(parent * remaining[0], remaining.slice(1), target)
    if(option1){
        return option1
    }
    return descend(parent + remaining[0], remaining.slice(1), target)
}


try {
  const data = fs.readFileSync('../inputs/day7.txt', 'utf8');

  var lines = data.split('\n')
  var sum = 0
  for(let i = 0; i < lines.length; i++){
    var parts = lines[i].split(':')
    var target = parseInt(parts[0])

    var operands = parts[1].split(' ').slice(1)

    for(let j = 0; j < operands.length; j++){
        operands[j] = parseInt(operands[j])
    }

    if(descend(operands[0], operands.slice(1), target)){
        sum += target
    }


  }

  console.log(sum)

} catch (err) {
    console.error(err);
  }