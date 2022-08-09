const express = require('express')
const app = express()
const port = 3000

// expects example - localhost:3000/?string=cos(x)^2&x=5.123
app.get('/', (req, res) => {
  const { exec } = require("child_process");
  console.log(req.query)
  exec(`./mai "${req.query.string}" "${req.query.x}"`, (error, stdout, stderr) => {
    console.log(stdout)
    res.send(stdout)
  });
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})
