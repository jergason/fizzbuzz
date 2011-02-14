// TODO browser js registry
// TODO online editing of js and html

var flashcards = [
  [1, "The Voice of Warning"],
  [2, "The Promises Made to the Fathers"],
  [3, "The works and the designs of God cannot be frustrated"],
  [4, "Oh ye that embark in the service of god"],
  [5, "the testimony of three witnesses"],
  [6, "the arrival of oliver cowdery"],
  [7, "john the revelator"],
  [8, "the spirit of revelation"],
  [9, "your bosom shall burn within you"],
  [10, "god's wisdom is greater than the cunning of the devil"],
  [11, "first seek to obtain my word"],
  [12, "revelation to Joseph Knight Sr"],
  [13, "the restoration of the aaronic priesthood"],
  [14, "revelation to david whitmer"],
  ["15-16", "revelations to john whitmer and peter whitmer jr"],
  [17, "revelation to the three witnesses"],
  [18, "the worth of a soul"],
  [19, "the gift of repentance"],
  [20, "the articles and covenants of the church"],
  [21, "his word shall ye receive as if from my own mouth"],
  [22, "baptism: a new and everlasting covenant"],
  [23, "strengthen the church continually"],
  [24, "declare my gospel as with the voice of a trump"],
]

function matchingCards(origcards) {
  var cards = origcards.slice(0);
  var current;

  cards.sort(function() {return 0.5 - Math.random()});

  function get() {
    current = cards.pop();
    return current && current[1];
  } 

  function peek() {
    return current[0];
  }

  function test(answer) {
    if (answer == current[0]) {
      return true;
    }
    return false;
  }
  return {
    get: get,
    test: test,
    peek: peek
  };
}

var game = matchingCards(flashcards);

var board = "" +
  "<form id='flash'>" +
    "<div id='question'></div>" +
    "<input id='answer' type='text' />" +
    "<input type='submit' value='submit' />" +
  "</form>";

$("body").html(board);
var q = game.get();
$("#question").text(q);
$("body").delegate('form#flash', 'submit', function (ev) {
  ev.preventDefault();
  if (game.test($("#answer").val())) {
    q = game.get();
    if (undefined === q) {
      alert("And now for the next round...");
      game = matchingCards(flashcards);
      q = game.get();
    }
    $("#question").text(q||'');
  } else {
    alert("Wrongo " + $("#answer").val() + ' ' + game.peek());
  }
  $("#answer").val('');
});
