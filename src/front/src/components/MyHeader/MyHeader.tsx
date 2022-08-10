import React, { useEffect, useState } from 'react';
import { getInput } from '../../app/graphSlice';
import { useAppDispatch, useAppSelector } from '../../app/hooks';
import MyInput from '../MyInput/MyInput';
import styles from './MyHeader.module.css'

const MyHeader = () => {
    const settings = useAppSelector(state => state.graph.settings)
    const [newSettings, setNewSetting] = useState({} as any)
    const useInputchange = (e: React.ChangeEvent) => {
        const key = e.target.id
        if (key === 'func') {
            setNewSetting({...newSettings, [key]: (e.target as HTMLInputElement).value})
        } else {
            setNewSetting({...newSettings, [key]: Number((e.target as HTMLInputElement).value)})
        }
    }

    const dispatch = useAppDispatch();
    useEffect(() => {
        if (JSON.stringify(newSettings) !== '{}')
            dispatch(getInput(newSettings));
    }, [newSettings, dispatch])

    return (<header className={styles.header}>
        <MyInput inputname={'func'} width={'wide'} callback={useInputchange} value={String(settings.func)}/>
        <div className={styles.lower_wrapper}>
            <MyInput  inputname={'x_min'} width={'narrow'} callback={useInputchange} value={String(settings.x_min)}/>
            <MyInput  inputname={'x_max'} width={'narrow'} callback={useInputchange} value={String(settings.x_max)}/>
            <MyInput  inputname={'step'} width={'narrow'} callback={useInputchange} value={String(settings.step)}/>
        </div>
        <div className={styles.btn + ' ' + styles.noselect}>Draw</div>
    </header>)
}

export default MyHeader;