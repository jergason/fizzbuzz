/*
 * Weds Oct 20th 2010
 *
 * Helping a friend with some homework, decided to do it for myself for fun.
 *
 * CS142 - BYU Fall Semester 2010 - Hotplate Lab
 * 
 * The spec is like this:
 *
 * use a 2-d array representing a (18x18) plate with 4 edges (20x20 total) touching
 * two sides against a maximum (100) temperature surface (the first and last rows)
 * and the others against a minimum (0) temperature surface (the first and last columns)
 *
 * Each instant the temperature of a given point on the plate (hotplate[x][y])
 * is calculated by averaging the top, bottom, left, and right points onto
 * the point itself.
 *
 * Find the number of instances it takes until the difference between the previous
 * and current temperature of the point which has changed the most in temperature
 * is less than 0.1 units.
 * 
 * Output the temperature of each point during that instant as a CSV.
 * View the results in a spreadsheet.
 *
 */

var HotPlate = {};
(function () {
  var hotplate = [
    [  0, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 ],
    [  0, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,   0 ]
  ];

  // This is code I used to generate the array above (with a few minor modifications)

  /*
  var result = "[\n", i, j;
  result += '[';
  for (j = 0; j < 20; j += 1) {
    result += '100, ';
  }
  result += '],\n';
  for (i = 2; i < 20; i += 1) {
    result += '[';
    for (j = 0; j < 20; j += 1) {
      result += '  0, ';
    }
    result += '],\n';
  }
  result += '[';
  for (j = 0; j < 20; j += 1) {
    result += '100, ';
  }
  result += '],\n';
  result += ']\n';

  console.log(result);
  */

  function find_steady_state_temperature() {
    var row,
      column,
      sum, // the sum of surrounding cells
      original, // the value of a cell before the change
      variance, // the max of all the variances
      allowed_variance = 0.1, // how much any cell may vary in temperature from one instance to the next.
      // 0.000000000000001 is the lowest you can go. If you try zero it will run forever (IEEE floating-point errors?)
      repeat = true, // if the base condition has yet to be met
      count = 0, // safeguard in case the base-case logic is incorrect
      max_count = 15000;

    while (true === repeat && count < max_count) {
      variance = 0;
      for (row = 1; row < 19; row += 1) {
        for (column = 1; column < 19; column += 1) {
          original = hotplate[row][column];

          sum = 0;
          sum += hotplate[row-1][column];
          sum += hotplate[row][column-1];
          sum += hotplate[row+1][column];
          sum += hotplate[row][column+1];
          hotplate[row][column] = sum / 4;

          variance = Math.max(hotplate[row][column] - original, variance);
        }
      }
      repeat = variance >= allowed_variance;
      count += 1;
    }
    if (max_count === count) {
      console.log("EPIC FAIL");
    } else {
      console.log("SUCCESS in just " + count + " instances!");
    }
  }

  function inspect() {
    var result = '', str = '';
    for (i = 0; i < 20; i += 1) {
      for (j = 0; j < 20; j += 1) {
        str = hotplate[i][j].toFixed(1).toString();
        while (str.length < 5) {
          str = ' ' + str;
        }
        str += ', ';
        result += str;
      }
      result += '\n';
    }

    console.log(result);
  }

  HotPlate.inspect = inspect;
  HotPlate.calculate_steady_state_temperature = find_steady_state_temperature;
}());

HotPlate.calculate_steady_state_temperature();
HotPlate.inspect();
