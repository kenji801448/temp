function isCorrect_(my_ans, ans_0, ans_1) {

  return my_ans != "" && (ans_0 == my_ans || ans_1 == my_ans);
}

function getgrade_(my_ans_list, correct_ans_matrix) {

    let grade = 0;
    for (let i = 0; i < my_ans_list.length; i++) {
      if (isCorrect_(my_ans_list[i], correct_ans_matrix[0][i], correct_ans_matrix[1][i])) {
        grade++;
      }
    }
    return grade;
}

/**
 * @customfunction
 */
function GRADECAL(my_ans_matrix, correct_ans_matrix) {
  
  if (Array.isArray(my_ans_matrix) && Array.isArray(correct_ans_matrix)) {
    return my_ans_matrix.map(my_ans_list =>
      getgrade_(my_ans_list, correct_ans_matrix)
    );
  }
  return "parameter 1 and 2 should be arrays.";
}

/**
 * @customfunction
 */
function COUNTIFLIST(my_ans_matrix, correct_ans_matrix) {

  let count = Array(my_ans_matrix[0].length);
  count.fill(0);
  for (let i = 0; i < my_ans_matrix.length; i++) {
    for (let j = 0; j < my_ans_matrix[0].length ; j++) {
      if (isCorrect_(my_ans_matrix[i][j], correct_ans_matrix[0][j], correct_ans_matrix[1][j])) {
        count[j]++;
      }
    }
  }
  return [count];
}
