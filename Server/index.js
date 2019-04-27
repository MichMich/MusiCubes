require('log-timestamp')(function() { return '[' + new Date().toString() + '] ' });

var config = require('./config.js')
var playlist = require('./playlist.js')
var express = require('express')
var axios = require('axios')
var app = express()

const baseUrl = config.sonos.baseUrl + '/' + config.sonos.room + '/'
const CancelToken = axios.CancelToken;
var cancelToken = null
var lastPlayerState = null
var lastCubeUid;

console.log(playlist)

/**
 * Start music based on a cube UID.
 */
app.get('/cube/:uid', function (req, res) {
  if (lastCubeUid === req.params.uid) return res.send('OK');

  const uri = getMusiCube(req.params.uid)
  if (!uri) {
    res.send('Unknown MusiCube: ' + req.params.uid)
    return console.log('Unknown MusiCube: ' + req.params.uid)
  }
  requestSonosUri(uri)
  lastCubeUid = req.params.uid;

  res.send('OK')
})

/**
 * Change the volume.
 */
app.get('/volume/:change', function (req, res) {
  if (req.params.change === 'up' || req.params.change === 'down') {
    requestSonosUri(req.params.change === 'up' ? 'volume/+3' : 'volume/-3', false);
  }

  res.send('OK')
});

/**
 * Skip song.
 */
app.get('/skip/:direction', function (req, res) {
  if (req.params.direction === 'next' || req.params.direction === 'previous') {
    requestSonosUri(req.params.direction, false)
  }

  res.send('OK')
});

/**
 * Toggle play/pause.
 */
app.get('/playpause', function (req, res) {
  requestSonosUri('playpause', false)

  res.send('OK')
});

/**
 * Log string.
 */
app.get('/log/:string', function (req, res) {
  console.log('[' + req.ip + '] ' + req.params.string)
  res.send('OK')
});

/**
 * Fetch player state.
 */
app.get('/state', function (req,res) {
  axios.get(baseUrl + 'state')
    .then(result => {
      res.send(result.data.playbackState)
    })
})

/**
 * Start webserver.
 */
app.listen(config.http.port, () => console.log(`MusiCubes app listening on port ${config.http.port}!`))

/**
 * Fetch playlist based on UID.
 *
 * @param {String} identifier
 */
function getMusiCube(identifier) {
  if (identifier == '00:00:00:00') return 'pause'
  if (identifier in playlist) return playlist[identifier]

  return false
}

/**
 * Request Sonos http api uri.
 * @param {String} uri
 * @param {Bool} cancelable
 */
function requestSonosUri(uri, cancelable = true) {
  console.log('Requesting: ' + uri)

  if (cancelable && cancelToken) {
    cancelToken.cancel();
  }

  var params = {};
  if (cancelable) {
    cancelToken = CancelToken.source();
    params = {
      cancelToken: cancelToken.token
    }
  }

  axios.get(baseUrl + uri, params)
    .then(result => {
      console.log('Request confirmed: ' + uri)
    })
    .catch(e => {
      if (axios.isCancel(e)) {
        return console.log('Request canceled: ', uri);
      }
      console.log(uri + ' is not a valid endpoint: ' + e)
    })
}
