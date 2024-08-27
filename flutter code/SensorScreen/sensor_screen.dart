import 'package:flutter/material.dart';
import 'package:flutter_firebase1/SensorScreen/components/body.dart';
import '../constants.dart';

class SensorScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: kBgColor,
      body: SensorScreenBody(),
    );
  }
}
