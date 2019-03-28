const PORT=3001;
const app = require('./app');
const server = app.listen(PORT, () => {
  console.log(`Express is running on port ${server.address().port}`);
});