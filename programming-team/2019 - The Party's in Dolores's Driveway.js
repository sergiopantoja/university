var readline = require('readline');

var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

rl.question('Please enter the initial driveway: ', function(answer) {
  var driveway = answer.split('');

  console.log('The initial order is ' + answer);

  rl.question('> ', function(n) {

      var leave = function() {
        rl.question('> ', function(answer) {
          if (answer.toLowerCase() === 'stop') {
            rl.close();
          }
          else {
            var index = driveway.indexOf(answer),
                removed;

            if (index < (driveway.length + 1) / 2) {
              removed = driveway.splice(0, index + 1);
              removed.pop();
              driveway = removed.reverse().concat(driveway);
            }
            else {
              removed = driveway.splice(index, Number.MAX_VALUE);
              driveway = driveway.concat(removed.reverse());
              driveway.pop();
            }

            console.log('After ' + answer + ' leaves, the order is ' + driveway.join(''));

            n--;
            if (n > 0) leave();
            else {
              console.log()
              rl.close();
            }

          }
        });
      };

      leave();
  });

});