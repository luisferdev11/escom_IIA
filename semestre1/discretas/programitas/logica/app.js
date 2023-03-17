function arrayEquals(a, b) {
  return (
    Array.isArray(a) &&
    Array.isArray(b) &&
    a.length === b.length &&
    a.every((val, index) => val === b[index])
  );
}

const OPERATORS = {
  nothing: (p) => p,
  and: (p, q) => p && q,
  or: (p, q) => p || q,
  not: (p) => !p,
  implicates: (p, q) => !p || q,
  biconditional: (p, q) => p === q,
};

const OPERATORS_SYMBOLS = {
  nothing: "",
  and: "^",
  or: "v",
  not: "~",
  implicates: "->",
  biconditional: "<->",
};

const inputs_tab1 = {
  p: [true, true, true, true, false, false, false, false],
  q: [true, true, false, false, true, true, false, false],
  r: [true, false, true, false, true, false, true, false],
};

// prettier-ignore
const inputs_tab2 = {
  p: [true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false],
  q: [true, true, true, true, false, false, false, false, true, true, true, true, false, false, false, false],
  r: [true, true, false, false, true, true, false, false, true, true, false, false, true, true, false, false],
  s: [true, false, true, false, true, false, true, false, true, false, true, false, true, false, true, false],
};

const formulario = document.getElementById("formulario");

formulario.addEventListener("submit", (e) => {
  event.preventDefault();

  const LOCAL_PROP_OP = {
    op11: document.getElementById("operators11").value,
    op12: document.getElementById("operators12").value,
    op13: document.getElementById("operators13").value,
    op14: document.getElementById("operators14").value,
    op15: document.getElementById("operators15").value,

    op21: document.getElementById("operators21").value,
    op22: document.getElementById("operators22").value,
    op23: document.getElementById("operators23").value,
    op24: document.getElementById("operators24").value,
    op25: document.getElementById("operators25").value,
    op26: document.getElementById("operators26").value,
  };

  const get_col = (operation, arr) => {
    const result = [];

    for (let i = 0; i < arr.length; i++) {
      result.push(OPERATORS[LOCAL_PROP_OP[operation]](arr[i]));
    }

    return result;
  };

  const get_col_2_var = (operation, arr1, arr2) => {
    const result = [];

    for (let i = 0; i < arr1.length; i++) {
      result.push(OPERATORS[LOCAL_PROP_OP[operation]](arr1[i], arr2[i]));
    }

    return result;
  };

  // //operaciones 1era tabla de verdad

  const get_tab1 = () => {
    const col1 = get_col("op11", inputs_tab1["p"]);
    const col2 = get_col("op15", inputs_tab1["r"]);

    // console.log(col1);
    // console.log(col2);

    const col3 = get_col_2_var("op12", col1, inputs_tab1["q"]);
    // console.log(col3);

    const col4 = get_col_2_var("op14", inputs_tab1["p"], col2);
    // console.log(col4);

    const final = get_col_2_var("op13", col3, col4);

    // console.log(final);

    const tabla = {
      p: inputs_tab1["p"],
      q: inputs_tab1["q"],
      r: inputs_tab1["r"],
      col1: col1,
      col2: col2,
      col3: col3,
      col4: col4,
      final: final,
    };

    return tabla;
  };

  // operaciones segunda tabla

  const get_tab2 = () => {
    const col1 = get_col("op24", inputs_tab2["p"]);
    const col2 = get_col("op26", inputs_tab2["s"]);

    // console.log(col1);
    // console.log(col2);

    const col3 = get_col_2_var("op21", inputs_tab2["p"], inputs_tab2["q"]);
    // console.log(col3);

    const col4 = get_col_2_var("op22", col3, inputs_tab2["r"]);
    // console.log(col4);

    const col5 = get_col_2_var("op25", col1, col2);
    // console.log(col5);

    const final = get_col_2_var("op23", col4, col5);
    // console.log(final);

    const table = {
      p: inputs_tab2["p"],
      q: inputs_tab2["q"],
      r: inputs_tab2["r"],
      s: inputs_tab2["s"],
      col1: col1,
      col2: col2,
      col3: col3,
      col4: col4,
      col5: col5,
      final: final,
    };
    return table;
  };

  const tabla1 = get_tab1();
  const tabla2 = get_tab2();

  console.log(tabla1);
  console.log(tabla2);

  // create table for tabla1
  const table1 = document.createElement("table");

  // create table header
  const header1 = document.createElement("tr");

  const header1Cells = [
    "p",
    "q",
    "r",
    "col1",
    "col2",
    `${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op11"]]}p ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op12"]]
    } q`,
    `p ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op14"]]} ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op15"]]
    }r`,
    `(${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op11"]]}p ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op12"]]
    } q) ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op13"]]} (p ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op14"]]
    } ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op15"]]}r)`,
  ];

  if (arrayEquals(tabla1.col2, inputs_tab1["r"])) {
    // header1Cells.splice(4, 1);
    delete header1Cells[4];
  } else {
    header1Cells[4] = "~r";
  }
  if (arrayEquals(tabla1.col1, inputs_tab1["p"])) {
    // header1Cells.splice(3, 1);
    delete header1Cells[3];
  } else {
    header1Cells[3] = "~p";
  }

  header1Cells.forEach((cell) => {
    const th = document.createElement("th");
    th.textContent = cell;
    header1.appendChild(th);
  });
  table1.appendChild(header1);

  // create table body
  for (let i = 0; i < tabla1.p.length; i++) {
    const row = document.createElement("tr");
    const cells = [
      tabla1.p[i],
      tabla1.q[i],
      tabla1.r[i],
      tabla1.col1[i],
      tabla1.col2[i],
      tabla1.col3[i],
      tabla1.col4[i],
      tabla1.final[i],
    ];

    if (header1Cells[3] == undefined) {
      // console.log(header1Cells[3]);
      cells[3] = undefined;
    }
    if (header1Cells[4] == undefined) {
      cells[4] = undefined;
    }

    // console.log(cells);

    cells.forEach((cell) => {
      if (cell != undefined) {
        const td = document.createElement("td");
        td.textContent = cell;
        row.appendChild(td);
      }
    });
    table1.appendChild(row);
  }

  // create table for tabla2
  const table2 = document.createElement("table");

  // create table header
  const header2 = document.createElement("tr");

  const header2Cells = [
    "p",
    "q",
    "r",
    "s",
    "col1",
    "col2",
    `p ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op21"]]} q`,
    `(p ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op21"]]} q) ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op22"]]
    } r`,
    `${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op24"]]} p ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op25"]]
    } ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op26"]]} s`,
    `[(p ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op21"]]} q) ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op22"]]
    } r] ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op23"]]} [${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op24"]]
    } p ${OPERATORS_SYMBOLS[LOCAL_PROP_OP["op25"]]} ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP["op26"]]
    } s]`,
  ];

  if (arrayEquals(tabla2.col2, inputs_tab2["s"])) {
    // header1Cells.splice(4, 1);
    delete header2Cells[5];
  } else {
    header2Cells[5] = "~s";
  }
  if (arrayEquals(tabla2.col1, inputs_tab2["p"])) {
    // header1Cells.splice(3, 1);
    delete header2Cells[4];
  } else {
    header2Cells[4] = "~p";
  }

  console.log(header2Cells);

  header2Cells.forEach((cell) => {
    const th = document.createElement("th");
    th.textContent = cell;
    header2.appendChild(th);
  });
  table2.appendChild(header2);

  // create table body
  for (let i = 0; i < tabla2.p.length; i++) {
    const row = document.createElement("tr");
    const cells = [
      tabla2.p[i],
      tabla2.q[i],
      tabla2.r[i],
      tabla2.s[i],
      tabla2.col1[i],
      tabla2.col2[i],
      tabla2.col3[i],
      tabla2.col4[i],
      tabla2.col5[i],
      tabla2.final[i],
    ];

    if (header2Cells[4] == undefined) {
      // console.log(header1Cells[3]);
      cells[4] = undefined;
    }
    if (header2Cells[5] == undefined) {
      cells[5] = undefined;
    }

    cells.forEach((cell) => {
      if (cell != undefined) {
        const td = document.createElement("td");
        td.textContent = cell;
        row.appendChild(td);
      }
    });
    table2.appendChild(row);
  }

  // add tables to the page
  const tableContainer = document.getElementById("table-container");
  tableContainer.innerHTML = "";
  tableContainer.appendChild(table1);
  tableContainer.appendChild(table2);
});
