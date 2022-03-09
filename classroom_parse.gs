function parse_grade_(grade_text) {

  let first_word = grade_text.split(" ")[0];
  let num = first_word.replace("Estigfend", "");
  return parseInt(num.substring(0, num.length / 2));
}

function text2int_(text) {
  
  return text.includes("ssigned") ? 0 : parse_grade_(text);
}

/**
 * @customfunction
 */
function CLASSROOMGRADE(input) {

  return Array.isArray(input) ? input.map(row => row.map(text2int_)) : text2int_(input);
}
