readline = require 'readline'

rl = readline.createInterface {input: process.stdin, output: process.stdout}

rl.question 'Please enter the initial driveway: ', (answer) ->
  driveway = answer.split ''
  console.log "The initial order is #{answer}"

  rl.question '> ', (n) ->

    leave = ->
      rl.question '> ', (answer) ->
        if answer.toLowerCase() is 'stop' then rl.close()
        else
          index = driveway.indexOf answer
          if index < (driveway.length + 1) / 2
            removed = driveway.splice 0, index+1
            removed.pop()
            driveway = removed.reverse().concat driveway
          else
            removed = driveway.splice index, Number.MAX_VALUE
            driveway = driveway.concat removed.reverse()
            driveway.pop()

          console.log "After #{answer} leaves, the order is #{driveway.join('')}"

          n--;
          if n > 0 then leave()
          else
            console.log()
            rl.close()
    leave()
