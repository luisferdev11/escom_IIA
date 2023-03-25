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

const isTaut = (arr) => {
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] !== true) {
      return false;
    }
  }
  return true;
};

const OPERATORS_SYMBOLS = {
  nothing: "",
  and: "^",
  or: "v",
  not: "~",
  implicates: "->",
  biconditional: "<->",
};

const calculatePrimitives = (n) => {
  let result = {};
  for (let i = 0; i < n; i++) {
    let varName = String.fromCharCode(112 + i); // "p" + i
    let values = [];
    for (let j = 0; j < Math.pow(2, n); j++) {
      values.push(Boolean(j & (1 << (n - i - 1))));
    }
    result[varName] = values.reverse();
  }
  return result;
};

const inputs_tab = calculatePrimitives(5);
console.log(inputs_tab);

const formulario = document.getElementById("formulario");

formulario.addEventListener("submit", (e) => {
  event.preventDefault();

  const LOCAL_PROP_OP = {
    op11: document.getElementById("operators11").value,
    op12: document.getElementById("operators12").value,
    op13: document.getElementById("operators13").value,

    op21: document.getElementById("operators21").value,
    op22: document.getElementById("operators22").value,
    op23: document.getElementById("operators23").value,

    op31: document.getElementById("operators31").value,
    op32: document.getElementById("operators32").value,
    op33: document.getElementById("operators33").value,

    op41: document.getElementById("operators41").value,
    op42: document.getElementById("operators42").value,
    op43: document.getElementById("operators43").value,

    op51: document.getElementById("operators51").value,
    op52: document.getElementById("operators52").value,
    op53: document.getElementById("operators53").value,
    op54: document.getElementById("operators54").value,
    op55: document.getElementById("operators55").value,

    and: "and",
    implicates: "implicates",
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

  const get_tab = () => {
    const A = get_col_2_var(
      "op12",
      get_col("op11", inputs_tab.p),
      get_col("op13", inputs_tab.q)
    );

    const B = get_col_2_var(
      "op22",
      get_col("op21", inputs_tab.q),
      get_col("op23", inputs_tab.r)
    );

    const C = get_col_2_var(
      "op32",
      get_col("op31", inputs_tab.r),
      get_col("op33", inputs_tab.s)
    );

    const D = get_col_2_var(
      "op42",
      get_col("op41", inputs_tab.s),
      get_col("op43", inputs_tab.t)
    );

    const E = get_col_2_var(
      "and",
      get_col_2_var("and", A, B),
      get_col_2_var("and", C, D)
    );

    const F = get_col_2_var(
      "op54",
      get_col_2_var(
        "op52",
        get_col("op51", inputs_tab.p),
        get_col("op53", inputs_tab.q)
      ),
      get_col("op55", inputs_tab.r)
    );

    const FINAL = get_col_2_var("implicates", E, F);

    const tabla = inputs_tab;

    tabla.A = A;
    tabla.B = B;
    tabla.C = C;
    tabla.D = D;
    tabla.E = E;
    tabla.F = F;
    tabla.FINAL = FINAL;

    return tabla;
  };

  const tabla = get_tab();

  console.log(tabla);

  // create table for tabla2
  const table = document.createElement("table");

  // create table header
  const header = document.createElement("tr");

  let headerCells = [
    "p",
    "q",
    "r",
    "s",
    "t",
    `${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op11]} p ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP.op12]
    } ${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op13]} q = A`,
    `${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op21]} q ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP.op22]
    } ${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op23]} r = B`,
    `${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op31]} r ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP.op32]
    } ${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op33]} s = C`,
    `${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op41]} s ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP.op42]
    } ${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op43]} t = D`,
    "A ^ B ^ C ^ D = E",
    `( ${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op51]} p ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP.op52]
    }${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op53]} q ) ${
      OPERATORS_SYMBOLS[LOCAL_PROP_OP.op54]
    } ${OPERATORS_SYMBOLS[LOCAL_PROP_OP.op55]} r = F`,
    "E -> F",
  ];

  headerCells.forEach((cell) => {
    const th = document.createElement("th");
    th.textContent = cell;
    header.appendChild(th);
  });
  table.appendChild(header);

  // create table body
  for (let i = 0; i < tabla.p.length; i++) {
    const row = document.createElement("tr");
    const cells = [
      tabla.p[i],
      tabla.q[i],
      tabla.r[i],
      tabla.s[i],
      tabla.t[i],
      tabla.A[i],
      tabla.B[i],
      tabla.C[i],
      tabla.D[i],
      tabla.E[i],
      tabla.F[i],
      tabla.FINAL[i],
    ];

    cells.forEach((cell) => {
      if (cell != undefined) {
        const td = document.createElement("td");
        td.textContent = cell;
        row.appendChild(td);
      }
    });
    table.appendChild(row);
  }

  const sexo = isTaut(tabla.FINAL);

  // add tables to the page
  const tableContainer = document.getElementById("table-container");
  tableContainer.innerHTML = "";
  if (sexo == true) {
    tableContainer.innerHTML = `<div class="box">
    <h2>Es un argumento válido</h2>
  </div>
  `;
  } else {
    tableContainer.innerHTML = `<div class="box">
    <h2>No es un argumento válido</h2>
  </div>
  `;
  }
  tableContainer.appendChild(table);
});
