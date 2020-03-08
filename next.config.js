const withTM = require('next-transpile-modules')([
  'bs-platform',
  '@jsiebern/bs-material-ui',
  '@mscharley/bs-material-ui-icons',
  're-classnames',
])

module.exports = withTM({
  pageExtensions: ['jsx', 'js', 'bs.js'],
})
