import React from "react";
import styles from "./MyInput.module.css";

export interface IMyInputProps {
  inputname: string;
  width: string;
  callback: (e: React.ChangeEvent) => void,
  value: string
}

const MyInput = (props: IMyInputProps) => {

    return (
    <div className={styles.input_wrapper}>
      <div
        className={[
          styles.label,
          props.width === "wide" ? styles.wide : styles.narrow,
        ].join(" ")}
      >
        {props.inputname}
      </div>
      <input
        value={props.value}
        id={props.inputname}
        className={[
          styles.input,
          props.width === "wide" ? styles.wide : styles.narrow,
        ].join(" ")}
        onChange={props.callback}
      ></input>
    </div>
  );
};

export default MyInput;
