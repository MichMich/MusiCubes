const playlist = {
    // Male
    '04:9a:63:b2': 'spotify/now/spotify:user:best-of-the-best:playlist:4Qp9icwIZ545w7rcI5irrW', // Robbie Williams
    '04:92:63:b2': 'spotify/now/spotify:user:george_michael:playlist:1Uv1EBo0pL7BzZ40afDrSi', // George Michael
    '04:8b:62:b2': 'spotify/now/spotify:user:kelchner:playlist:7ztZBGd2s1iTCPEQUiNJ7i', // Michael Bublé
    '04:96:63:b2': 'spotify/now/spotify:album:3VWrUk4vBznMYXGMPc7dRB', // Queen
    '04:8e:63:b2': 'spotify/now/spotify:album:1cW0de5T5fdedlS4YqvyCv', // Lenny Kravitz
    '04:29:3c:ba': 'spotify/now/spotify:user:ogietayag:playlist:6Uqvol9bqJkxEDxZFDdm3h', // Dire Straits

    // Female
    '04:d2:3d:ba': 'spotify/now/spotify:user:micahjesse:playlist:4AE2ERkTNZjhrhMQCx5DA5', // Beyonce
    '04:25:3c:ba': 'spotify/now/spotify:user:hafizarif13:playlist:69kTva1V51Ow4fQFP1LUxG', // Taylor Swift
    '04:ce:3d:ba': 'spotify/now/spotify:user:fredrikkarlsson96:playlist:62HtzJxggBFb1E2O005bUb', // Lady Gaga
    '04:c1:3d:ba': 'spotify/now/spotify:user:1191809760:playlist:76qjUjaQk7F9cBtoniKP1D', // Katy Perry
    '04:d6:3d:ba': 'spotify/now/spotify:user:felipefoggia:playlist:33EL1piBW36KuSiPGV6QRt', // Ariana Grande
    '04:da:3d:ba': 'spotify/now/spotify:user:216h7ziuz78j5tsieu71c4egy:playlist:0DZps7m41jMAhJO3dvNH3a', // Rihanna

    // Alt
    '04:d7:64:b2': 'spotify/now/spotify:user:franjav1984:playlist:2KVqduM0LCzmY5zfz2DDcQ', // Enigma
    '04:22:3d:ba': 'spotify/now/spotify:album:2FhkO0XspLqBtcanjn5Uzk', // Enya
    '04:df:64:b2': 'spotify/now/spotify:album:578k9Ef0aNVmpRxkTiQgua', // Bliss
    '04:db:64:b2': 'spotify/now/spotify:album:6xKKUwzK45UoA2wO5w1wYd', // Conjure One

    // EDM
    '04:31:3c:ba': 'spotify/now/spotify:user:alainpossiel:playlist:7q0BbZVzYfPAZJPk1KE7KE', // Martin Garixx
    '04:97:3d:ba': 'spotify/now/spotify:user:1185996266:playlist:1pdfLg56vOl9TYPMeKg9jG', // Massive Attack
    '04:9f:3d:ba': 'spotify/now/spotify:user:jtron44:playlist:1VUVQp70v2jULYnjd0JRln', // Tiesto
    '04:93:3d:ba': 'spotify/now/spotify:user:1128800583:playlist:4b7jEl8w7xtuieOLw3V6sj', // Avici
    '04:8f:3d:ba': 'spotify/now/spotify:user:daniel_lawson9999:playlist:6jeSKyPBU24fdGlYfOaSnx', // Daft Punk
    '04:9b:3d:ba': 'spotify/now/spotify:user:11129072476:playlist:5jsEhfhi9oL5NJ1hhS1pW0', // Armin van Buuren

    // Radio
    '04:8c:60:b2': 'favorite/BLUE MARLIN IBIZA RADIO', // Blue Marlin
    '04:ac:62:b2': 'favorite/Classic', // Klassiek
    '04:a8:62:b2': 'favorite/Koffee', // Koffee
    '04:0e:3d:ba': 'spotify/now/spotify:user:defected.records:playlist:08M2kTqmlPNHygrNfrZJuQ', // Defected
    '04:90:60:b2': 'favorite/538', // 538
    '04:8d:61:b2': 'favorite/Ibiza Global Radio', // Ibiza Global Radio

    // Moments
    '04:16:3d:ba': 'spotify/now/spotify:user:spotify:playlist:37i9dQZF1DX0Yxoavh5qJV', // Kerst
    '04:ec:3d:ba': 'spotify/now/spotify:user:1141402282:playlist:0y9f8tbQEyA2yJUCvQB9sw', // Birthday
    '04:f0:3d:ba': 'spotify/now/spotify:user:11175854168:playlist:20iG6ZtP6vDr146idkQCv4', // Sinterklaas

    // Kids
    '04:0a:3d:ba': 'spotify/now/spotify:user:c.koekoek:playlist:0MpXwWIaYmiodOK6gPlBbM', // Juf Roos
    '04:c6:3d:ba': 'spotify/now/spotify:album:1LVBv18hDtL8oyXJjARzSR', // Fien en Teun
    '04:ca:3d:ba': 'spotify/now/spotify:user:artsycloe90:playlist:5cgpouN7Z53NTyENJXoi7e', // Disney
    '04:de:3d:ba': 'playlist/kinderliedjes', // Kinderliedjes

    // Playlists
    '04:ca:64:b2': 'favorite/Lekkere%20nummertjes', // Lekkere Nummertjes
    '04:1a:3d:ba': 'spotify/now/spotify:user:9nkutxcrnrdggvmk4qtj8a2jk:playlist:3WX9wqcPBnLqGR2pErkZ1G', // Chillout
    '04:c3:63:b2': 'spotify/now/spotify:user:21ifzjxggdajdpc4w6iqxslkq:playlist:4hfe8itOfwwijAHHOlI6pp', // Top 40
    '04:ce:64:b2': 'favorite/Discover%20Weekly', // Discover Weekly
    '04:d3:64:b2': 'spotify/now/spotify:user:spotify:playlist:37i9dQZF1DWZz0dmtcndFR', // Party

    // Moods
    '04:b8:3d:ba': 'spotify/now/spotify:user:spotify:playlist:37i9dQZF1DX5dJCW6dyCUe', // Morning
    '04:9a:62:b2': 'spotify/now/spotify:user:vipmusik-fr:playlist:7kzI9Z2lU67PzhRaaiacC0', // Summer
    '04:a3:62:b2': 'spotify/now/spotify:user:eating_tv:playlist:0e1zsySwa4K8yu96GIBVZq', // Work
    '04:9e:62:b2': 'spotify/now/spotify:user:spotify:playlist:37i9dQZF1DX4H7FFUM2osB', // Winter
    '04:1e:3d:ba': 'spotify/now/spotify:user:spotify:playlist:37i9dQZF1DWZz0dmtcndFR', // Party
    '04:bc:3d:ba': 'spotify/now/spotify:user:spotify:playlist:37i9dQZF1DWU0ScTcjJBdj', // Relaxing
}

module.exports = playlist
