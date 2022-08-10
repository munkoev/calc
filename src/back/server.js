const express = require("express");
const cors = require("cors");
const { nextTick } = require("process");
const app = express();
const port = 3000;

app.use(cors({ origin: "*" }));

// expects example - localhost:3000/?string=cos(x)^2&x=5.123
app.get("/", (req, res, next) => {
  const { exec } = require("child_process");
  if (
    typeof req.query.string !== "undefined" &&
    typeof req.query.xmin !== "undefined" &&
    typeof req.query.xmax !== "undefined" &&
    typeof req.query.step !== "undefined"
  ) {
    exec(
      `./mai "${req.query.string}" "${req.query.xmin}" "${req.query.xmax}" "${req.query.step}"`,
      (error, stdout, stderr) => {
        if (error) {
          next(stderr);
        } else {
          res.send(stdout);
        }
      }
    );
  } else if (
    typeof req.query.string !== "undefined" &&
    typeof req.query.x !== "undefined"
  ) {
    exec(
      `./mai "${req.query.string}" "${req.query.x}"`,
      (error, stdout, stderr) => {
        if (error) {
          next(stderr);
        } else {
          res.send(stdout);
        }
      }
    );
  } else {
    throw new Error('BROKEN');
  }
});

app.listen(port, () => {
  console.log(`Express listening on port ${port}`);
});
