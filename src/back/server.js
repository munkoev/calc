const express = require('express')
const cors = require('cors');
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

app.use(cors())

// app.use(cors({
//   origin: 'http://yourapp.com'
// }));

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})

