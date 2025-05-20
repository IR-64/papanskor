import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'new.dart'; // Impor file new.dart

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: ScoreboardControl(),
    );
  }
}

class ScoreboardControl extends StatefulWidget {
  @override
  _ScoreboardControlState createState() => _ScoreboardControlState();
}

class _ScoreboardControlState extends State<ScoreboardControl> {
  TextEditingController teamAController = TextEditingController();
  TextEditingController teamBController = TextEditingController();
  TextEditingController setAController = TextEditingController();
  TextEditingController setBController = TextEditingController();
  TextEditingController ta1Controller = TextEditingController();
  TextEditingController ta2Controller = TextEditingController();
  TextEditingController tb1Controller = TextEditingController();
  TextEditingController tb2Controller = TextEditingController();

  int round = 1;
  bool isCounting = false;

  // Mengirim data ke NodeMCU
  void sendDataToESP(String endpoint, String value) async {
    String url = 'http://192.168.4.1/$endpoint?value=$value';
    try {
      final response = await http.get(Uri.parse(url));
      if (response.statusCode == 200) {
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(content: Text('Data sent successfully')),
        );
      } else {
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(content: Text('Failed to send data: ${response.statusCode}')),
        );
      }
    } catch (e) {
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text('Error sending data: $e')),
      );
    }
  }

  void startCounting() {
    setState(() {
      isCounting = true;
    });
    sendDataToESP('start', '1');
  }

  void pauseCounting() {
    setState(() {
      isCounting = false;
    });
    sendDataToESP('pause', '1');
  }

  void resetTimer() {
    setState(() {
      isCounting = false;
    });
    sendDataToESP('reset', '1');
  }

  void updateRound() {
    setState(() {
      round++;
    });
    sendDataToESP('round', round.toString());
  }

  void resetRound() {
    setState(() {
      round = 1;
    });
    sendDataToESP('round', round.toString());
  }

  void updateTeams() {
    String teamA = teamAController.text;
    String teamB = teamBController.text;
    sendDataToESP('teamA', teamA);
    sendDataToESP('teamB', teamB);
  }

  void updateGameSettings() {
    sendDataToESP('setA', setAController.text);
    sendDataToESP('setB', setBController.text);
    sendDataToESP('TA1', ta1Controller.text);
    sendDataToESP('TA2', ta2Controller.text);
    sendDataToESP('TB1', tb1Controller.text);
    sendDataToESP('TB2', tb2Controller.text);
  }

  // Navigasi ke halaman baru
  void navigateToNewPage() {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => NewPage()),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Scoreboard Control')),
      body: SingleChildScrollView(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            TextField(
              controller: teamAController,
              decoration: InputDecoration(labelText: 'Team A'),
            ),
            TextField(
              controller: teamBController,
              decoration: InputDecoration(labelText: 'Team B'),
            ),
            SizedBox(height: 10),
            ElevatedButton(
              onPressed: updateTeams,
              child: Text('Update Teams'),
            ),
            Divider(),
            TextField(
              controller: setAController,
              decoration: InputDecoration(labelText: 'Set A'),
            ),
            TextField(
              controller: setBController,
              decoration: InputDecoration(labelText: 'Set B'),
            ),
            TextField(
              controller: ta1Controller,
              decoration: InputDecoration(labelText: 'TA1'),
            ),
            TextField(
              controller: ta2Controller,
              decoration: InputDecoration(labelText: 'TA2'),
            ),
            TextField(
              controller: tb1Controller,
              decoration: InputDecoration(labelText: 'TB1'),
            ),
            TextField(
              controller: tb2Controller,
              decoration: InputDecoration(labelText: 'TB2'),
            ),
            SizedBox(height: 10),
            ElevatedButton(
              onPressed: updateGameSettings,
              child: Text('Update Game Settings'),
            ),
            Divider(),
            ElevatedButton(
              onPressed: updateRound,
              child: Text('Next Round ($round)'),
            ),
            ElevatedButton(
              onPressed: resetRound,
              child: Text('Reset Round'),
            ),
            Divider(),
            ElevatedButton(
              onPressed: startCounting,
              child: Text('Start Timer'),
            ),
            ElevatedButton(
              onPressed: pauseCounting,
              child: Text('Pause Timer'),
            ),
            ElevatedButton(
              onPressed: resetTimer,
              child: Text('Reset Timer'),
            ),
            ElevatedButton(
              onPressed: navigateToNewPage,
              child: Text('Go to New Page'),
            ),
          ],
        ),
      ),
    );
  }
}
