var config = require('./config.js')
var playlist = require('./playlist.js')
var express = require('express')
var axios = require('axios')
var app = express()

const baseUrl = config.sonos.baseUrl + '/' + config.sonos.room + '/'
const CancelToken = axios.CancelToken;
var cancelToken = null
var lastPlayerState = null

console.log(playlist)

app.get('/cube/:uid', function (req, res) {
  // console.log(req.params)

  const uri = getMusiCube(req.params.uid)
  if (!uri) {
    res.send('Unknown MusiCube: ' + req.params.uid)
    return console.log('Unknown MusiCube: ' + req.params.uid)
  }
  requestSonosUri(uri)
  res.send('OK')
})
app.get('/button/:button/:state', function (req, res) {
  // console.log(req.params)

  if (req.params.button == '0' && req.params.state == '1') {
    requestSonosUri('volume/+3')
  } else if (req.params.button == '1' && req.params.state == '1') {
    requestSonosUri('volume/-3')
  }

  res.send('OK')
})

app.get('/state', function (req,res) {
  axios.get(baseUrl + 'state')
    .then(result => {
      res.send(result.data.playbackState)
    })
})

app.listen(config.http.port, () => console.log(`MusiCubes app listening on port ${config.http.port}!`))

function getMusiCube(identifier) {
  if (identifier == '00:00:00:00') return 'pause'
  if (identifier in playlist) return playlist[identifier]

  return false
}

function requestSonosUri(uri) {
  console.log('Requesting: ' + uri)

  if (cancelToken) {
    cancelToken.cancel();
  }

  cancelToken = CancelToken.source();
  axios.get(baseUrl + uri,{
    cancelToken: cancelToken.token
  })
    .then(result => {
      console.log('Request confirmed: ' + uri)
    })
    .catch(e => {
      if (axios.isCancel(e)) {
        return console.log('Request canceled: ', uri);
      }
      console.log(uri + ' is not a valid endpoint.')
    })
}